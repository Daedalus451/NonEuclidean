#pragma once

#include <array>

struct tagRAWINPUT;

class Input
{
public:
  Input();

  void EndFrame();
  void UpdateRaw(const tagRAWINPUT* raw);

  // Keyboard
  std::array<bool, 256> key{};
  std::array<bool, 256> key_press{};

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
