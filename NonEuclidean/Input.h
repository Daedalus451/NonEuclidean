#pragma once

struct tagRAWINPUT;

class Input
{
public:
  Input();

  void EndFrame();
  void UpdateRaw(const tagRAWINPUT* raw);

  // Keyboard
  bool key[256];
  bool key_press[256];

  // Mouse
  bool mouse_button[3];
  bool mouse_button_press[3];
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
