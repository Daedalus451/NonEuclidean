#include "Input.h"

#include <algorithm>
#include <memory>

#include "GameHeader.h"

Input::Input() = default;

void Input::EndFrame()
{
  std::fill(key_press.begin(), key_press.end(), false);
  std::fill(mouse_button_press.begin(), mouse_button_press.end(), false);
  mouse_dx = mouse_dx * GH::MOUSE_SMOOTH + mouse_ddx * (1.0f - GH::MOUSE_SMOOTH);
  mouse_dy = mouse_dy * GH::MOUSE_SMOOTH + mouse_ddy * (1.0f - GH::MOUSE_SMOOTH);
  mouse_ddx = 0.0f;
  mouse_ddy = 0.0f;
}

void Input::UpdateRaw()
{
  int mouse_x = 0;
  int mouse_y = 0;
  uint32_t state = SDL_GetRelativeMouseState(&mouse_x, &mouse_y);
  mouse_dx = static_cast<float>(mouse_x);
  mouse_dy = static_cast<float>(mouse_y);

  if(state & SDL_BUTTON(SDL_BUTTON_LEFT))
  {
    mouse_button[0] = true;
    mouse_button_press[0] = true;
  }
  if(state & SDL_BUTTON(SDL_BUTTON_MIDDLE))
  {
    mouse_button[1] = true;
    mouse_button_press[1] = true;
  }
  if(state & SDL_BUTTON(SDL_BUTTON_RIGHT))
  {
    mouse_button[2] = true;
    mouse_button_press[2] = true;
  }

  // read key state
  const uint8_t* immediate_keys = SDL_GetKeyboardState(nullptr);

  for(size_t i = 0; i < SDL_NUM_SCANCODES; i++)
  {
    key[i] = static_cast<bool>(immediate_keys[i]);
    key_press[i] = static_cast<bool>(immediate_keys[i]);
  }
}
