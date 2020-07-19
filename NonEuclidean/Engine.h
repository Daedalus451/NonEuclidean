#pragma once

#include <memory>
#include <vector>

#define NOMINMAX

#include <GL/glew.h>
#include <Windows.h>

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

  LRESULT WindowProc(HWND hCurWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

  const Player& GetPlayer() const
  {
    return *player;
  }
  float NearestPortalDist() const;

private:
  void CreateGLWindow();
  void InitGLObjects();
  void DestroyGLObjects();
  void SetupInputs();
  void ConfineCursor();
  void ToggleFullscreen();

  HDC hDC = nullptr; // device context
  HGLRC hRC = nullptr; // opengl context
  HWND hWnd = nullptr; // window
  HINSTANCE hInstance = nullptr; // process id

  LONG iWidth = 0; // window width
  LONG iHeight = 0; // window height
  bool isFullscreen = false; // fullscreen state

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
