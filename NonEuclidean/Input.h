#pragma once

#include <array>

#include <SDL2/SDL.h>

class Input
{
public:
  Input();

  void EndFrame();
  void UpdateRaw();

  // Keyboard
  std::array<bool, SDL_NUM_SCANCODES> key{};
  std::array<bool, SDL_NUM_SCANCODES> key_press{};

  // Mouse
  std::array<bool, 3> mouse_button{};
  std::array<bool, 3> mouse_button_press{};
  float mouse_dx = 0.0f;
  float mouse_dy = 0.0f;
  float mouse_ddx = 0.0f;
  float mouse_ddy = 0.0f;

  // Joystick
  // TODO:

  // Bindings
  // TODO:

  // Calibration
  // TODO:
};
