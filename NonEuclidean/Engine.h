#pragma once

#include <memory>
#include <vector>

#include <GL/glew.h>

#include <SDL2/SDL.h>

#include "Camera.h"
#include "GameHeader.h"
#include "Input.h"
#include "Object.h"
#include "Player.h"
#include "Portal.h"
#include "Scene.h"
#include "Sky.h"
#include "Timer.h"

class Engine
{
public:
  Engine();
  ~Engine();

  int Run();
  void Update();
  void Render(const Camera& cam, GLuint curFBO, const Portal* skipPortal);
  void LoadScene(int ix);

  const Player& GetPlayer() const
  {
    return *player;
  }
  float NearestPortalDist() const;

private:
  void CreateGLWindow();
  void InitGLObjects();
  void DestroyGLObjects();
  void ConfineCursor();

  SDL_Window* window = nullptr;
  SDL_GLContext glContext = nullptr;
  int iHeight = 0;
  int iWidth = 0;

  Camera main_cam;
  Input input;
  Timer timer;

  std::vector<std::shared_ptr<Object>> vObjects;
  std::vector<std::shared_ptr<Portal>> vPortals;
  std::shared_ptr<Sky> sky;
  std::shared_ptr<Player> player;

  GLint occlusionCullingSupported = 0;

  std::vector<std::shared_ptr<Scene>> vScenes;
  std::shared_ptr<Scene> curScene;
};
