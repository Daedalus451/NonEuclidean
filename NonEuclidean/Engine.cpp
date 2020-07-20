#include "Engine.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <limits>

#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Level4.h"
#include "Level5.h"
#include "Level6.h"
#include "Physical.h"

Engine* GH::ENGINE = nullptr;
Player* GH::PLAYER = nullptr;
const Input* GH::INPUT = nullptr;
int GH::REC_LEVEL = 0;
int64_t GH::FRAME = 0;

Engine::Engine()
{
  GH::ENGINE = this;
  GH::INPUT = &input;

  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    throw std::runtime_error("failed to initialize SDL");
  }

  CreateGLWindow();
  InitGLObjects();

  ConfineCursor();

  player = std::make_shared<Player>();
  GH::PLAYER = player.get();

  vScenes.push_back(std::make_shared<Level1>());
  vScenes.push_back(std::make_shared<Level2>(3));
  vScenes.push_back(std::make_shared<Level2>(6));
  vScenes.push_back(std::make_shared<Level3>());
  vScenes.push_back(std::make_shared<Level4>());
  vScenes.push_back(std::make_shared<Level5>());
  vScenes.push_back(std::make_shared<Level6>());

  LoadScene(0);

  sky = std::make_shared<Sky>();
}

Engine::~Engine()
{
  if(glContext)
  {
    SDL_GL_DeleteContext(glContext);
  }
  if(window)
  {
    SDL_DestroyWindow(window);
  }
}

int Engine::Run()
{
  // Setup the timer
  const int64_t ticks_per_step = timer.SecondsToTicks(GH::DT);
  int64_t cur_ticks = timer.GetTicks();
  GH::FRAME = 0;

  // Game loop
  while(true)
  {
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT)
      {
        break;
      }
      else if(event.type == SDL_WINDOWEVENT)
      {
        if(event.window.event == SDL_WINDOWEVENT_RESIZED)
        {
          iWidth = event.window.data1;
          iHeight = event.window.data2;
          glViewport(0, 0, iWidth, iHeight);
        }
      }
    }

    input.UpdateRaw();

    if(input.key_press[SDL_SCANCODE_ESCAPE])
    {
      break;
    }

    if(input.key_press[SDL_SCANCODE_1])
    {
      LoadScene(0);
    }
    else if(input.key_press[SDL_SCANCODE_2])
    {
      LoadScene(1);
    }
    else if(input.key_press[SDL_SCANCODE_3])
    {
      LoadScene(2);
    }
    else if(input.key_press[SDL_SCANCODE_4])
    {
      LoadScene(3);
    }
    else if(input.key_press[SDL_SCANCODE_5])
    {
      LoadScene(4);
    }
    else if(input.key_press[SDL_SCANCODE_6])
    {
      LoadScene(5);
    }
    else if(input.key_press[SDL_SCANCODE_7])
    {
      LoadScene(6);
    }

    // Used fixed time steps for updates
    const int64_t new_ticks = timer.GetTicks();
    for(int i = 0; cur_ticks < new_ticks && i < GH::MAX_STEPS; ++i)
    {
      Update();
      cur_ticks += ticks_per_step;
      GH::FRAME += 1;
      input.EndFrame();
    }
    cur_ticks = (cur_ticks < new_ticks ? new_ticks : cur_ticks);

    // Setup camera for rendering
    const float n = std::clamp(NearestPortalDist() * 0.5f, GH::NEAR_MIN, GH::NEAR_MAX);
    main_cam.worldView = player->WorldToCam();
    main_cam.SetSize(iWidth, iHeight, n, GH::FAR_DIST);
    main_cam.UseViewport();

    // Render scene
    GH::REC_LEVEL = GH::MAX_RECURSION;
    Render(main_cam, 0, nullptr);
    SDL_GL_SwapWindow(window);
  }

  DestroyGLObjects();
  return 0;
}

void Engine::LoadScene(int ix)
{
  // Clear out old scene
  if(curScene)
  {
    curScene->Unload();
  }

  PObjectVec tempObjects;
  PPortalVec tempPortals;

  std::swap(tempObjects, vObjects);
  std::swap(tempPortals, vPortals);

  player->Reset();

  // Create new scene
  curScene = vScenes[ix];
  curScene->Load(vObjects, vPortals, *player);
  vObjects.push_back(player);
}

void Engine::Update()
{
  // Update
  for(size_t i = 0; i < vObjects.size(); ++i)
  {
    assert(vObjects[i].get());
    vObjects[i]->Update();
  }

  // Collisions
  // For each physics object
  for(size_t i = 0; i < vObjects.size(); ++i)
  {
    Physical* physical = vObjects[i]->AsPhysical();
    if(!physical)
    {
      continue;
    }
    Matrix4 worldToLocal = physical->WorldToLocal();

    // For each object to collide with
    for(size_t j = 0; j < vObjects.size(); ++j)
    {
      if(i == j)
      {
        continue;
      }
      Object& obj = *vObjects[j];
      if(!obj.mesh)
      {
        continue;
      }

      // For each hit sphere
      for(size_t s = 0; s < physical->hitSpheres.size(); ++s)
      {
        // Brings point from collider's local coordinates to hits's local coordinates.
        const Sphere& sphere = physical->hitSpheres[s];
        Matrix4 worldToUnit = sphere.LocalToUnit() * worldToLocal;
        Matrix4 localToUnit = worldToUnit * obj.LocalToWorld();
        Matrix4 unitToWorld = worldToUnit.Inverse();

        // For each collider
        for(size_t c = 0; c < obj.mesh->colliders.size(); ++c)
        {
          Vector3 push;
          const Collider& collider = obj.mesh->colliders[c];
          if(collider.Collide(localToUnit, push))
          {
            // If push is too small, just ignore
            push = unitToWorld.MulDirection(push);
            vObjects[j]->OnHit(*physical, push);
            physical->OnCollide(*vObjects[j], push);

            worldToLocal = physical->WorldToLocal();
            worldToUnit = sphere.LocalToUnit() * worldToLocal;
            localToUnit = worldToUnit * obj.LocalToWorld();
            unitToWorld = worldToUnit.Inverse();
          }
        }
      }
    }
  }

  // Portals
  for(size_t i = 0; i < vObjects.size(); ++i)
  {
    Physical* physical = vObjects[i]->AsPhysical();
    if(physical)
    {
      for(size_t j = 0; j < vPortals.size(); ++j)
      {
        if(physical->TryPortal(*vPortals[j]))
        {
          break;
        }
      }
    }
  }
}

void Engine::Render(const Camera& cam, GLuint curFBO, const Portal* skipPortal)
{
  // Clear buffers
  if(GH::USE_SKY)
  {
    glClear(GL_DEPTH_BUFFER_BIT);
    sky->Draw(cam);
  }
  else
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  // Create queries (if applicable)
  std::array<GLuint, GH::MAX_PORTALS> queries{};
  std::array<GLuint, GH::MAX_PORTALS> drawTest{};
  assert(vPortals.size() <= GH::MAX_PORTALS);
  if(occlusionCullingSupported)
  {
    glGenQueriesARB((GLsizei) vPortals.size(), queries.data());
  }

  // Draw scene
  for(size_t i = 0; i < vObjects.size(); ++i)
  {
    vObjects[i]->Draw(cam, curFBO);
  }

  // Draw portals if possible
  if(GH::REC_LEVEL > 0)
  {
    // Draw portals
    GH::REC_LEVEL -= 1;
    if(occlusionCullingSupported && GH::REC_LEVEL > 0)
    {
      glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
      glDepthMask(GL_FALSE);
      for(size_t i = 0; i < vPortals.size(); ++i)
      {
        if(vPortals[i].get() != skipPortal)
        {
          glBeginQueryARB(GL_SAMPLES_PASSED_ARB, queries[i]);
          vPortals[i]->DrawPink(cam);
          glEndQueryARB(GL_SAMPLES_PASSED_ARB);
        }
      }
      for(size_t i = 0; i < vPortals.size(); ++i)
      {
        if(vPortals[i].get() != skipPortal)
        {
          glGetQueryObjectuivARB(queries[i], GL_QUERY_RESULT_ARB, &drawTest[i]);
        }
      };
      glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
      glDepthMask(GL_TRUE);
      glDeleteQueriesARB((GLsizei) vPortals.size(), queries.data());
    }
    for(size_t i = 0; i < vPortals.size(); ++i)
    {
      if(vPortals[i].get() != skipPortal)
      {
        if(occlusionCullingSupported && (GH::REC_LEVEL > 0) && (drawTest[i] == 0))
        {
          continue;
        }
        else
        {
          vPortals[i]->Draw(cam, curFBO);
        }
      }
    }
    GH::REC_LEVEL += 1;
  }

#if 0
  //Debug draw colliders
  for (size_t i = 0; i < vObjects.size(); ++i) {
    vObjects[i]->DebugDraw(cam);
  }
#endif
}

void Engine::CreateGLWindow()
{
  iWidth = GH::SCREEN_WIDTH;
  iHeight = GH::SCREEN_HEIGHT;

  window =
    SDL_CreateWindow(GH::TITLE, GH::SCREEN_X, GH::SCREEN_Y, iWidth, iHeight,
                     SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | (GH::START_FULLSCREEN ? SDL_WINDOW_FULLSCREEN : 0));
  if(!window)
  {
    throw std::runtime_error("failed to create window");
  }

  glContext = SDL_GL_CreateContext(window);
  if(!glContext)
  {
    throw std::runtime_error("failed to create GL context");
  }

  SDL_SetWindowResizable(window, SDL_TRUE);
}

void Engine::InitGLObjects()
{
  // Initialize extensions
  if(glewInit() != GLEW_OK)
  {
    throw std::runtime_error("failed to initialize glew");
  }

  // Basic global variables
  glClearColor(0.6f, 0.9f, 1.0f, 1.0f);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);

  // Check GL functionality
  glGetQueryiv(GL_SAMPLES_PASSED_ARB, GL_QUERY_COUNTER_BITS_ARB, &occlusionCullingSupported);

  if(SDL_GL_SetSwapInterval(-1) != 0)
  {
    SDL_GL_SetSwapInterval(1);
  }
}

void Engine::DestroyGLObjects()
{
  curScene->Unload();
  vObjects.clear();
  vPortals.clear();
}

void Engine::ConfineCursor()
{
  if(GH::HIDE_MOUSE)
  {
    SDL_SetRelativeMouseMode(SDL_TRUE);
    SDL_SetWindowGrab(window, SDL_TRUE);
  }
}

float Engine::NearestPortalDist() const
{
  float dist = std::numeric_limits<float>::max();
  for(size_t i = 0; i < vPortals.size(); ++i)
  {
    dist = std::min(dist, vPortals[i]->DistTo(player->pos));
  }
  return dist;
}
