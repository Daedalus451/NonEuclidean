#include "Input.h"

#include <memory>

#define NOMINMAX

#include <Windows.h>

#include "GameHeader.h"

Input::Input() = default;

void Input::EndFrame()
{
  std::memset(key_press.data(), 0, key_press.size());
  std::memset(mouse_button_press.data(), 0, mouse_button_press.size());
  mouse_dx = mouse_dx * GH::MOUSE_SMOOTH + mouse_ddx * (1.0f - GH::MOUSE_SMOOTH);
  mouse_dy = mouse_dy * GH::MOUSE_SMOOTH + mouse_ddy * (1.0f - GH::MOUSE_SMOOTH);
  mouse_ddx = 0.0f;
  mouse_ddy = 0.0f;
}

void Input::UpdateRaw(const tagRAWINPUT* raw)
{
  if(raw->header.dwType == RIM_TYPEMOUSE)
  {
    if(raw->data.mouse.usFlags == MOUSE_MOVE_RELATIVE)
    {
      mouse_ddx += raw->data.mouse.lLastX;
      mouse_ddy += raw->data.mouse.lLastY;
    }
    if(raw->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_DOWN)
    {
      mouse_button[0] = true;
      mouse_button_press[0] = true;
    }
    if(raw->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_DOWN)
    {
      mouse_button[1] = true;
      mouse_button_press[1] = true;
    }
    if(raw->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_DOWN)
    {
      mouse_button[2] = true;
      mouse_button_press[2] = true;
    }
    if(raw->data.mouse.usButtonFlags & RI_MOUSE_LEFT_BUTTON_UP)
      mouse_button[0] = false;
    if(raw->data.mouse.usButtonFlags & RI_MOUSE_MIDDLE_BUTTON_UP)
      mouse_button[1] = false;
    if(raw->data.mouse.usButtonFlags & RI_MOUSE_RIGHT_BUTTON_UP)
      mouse_button[2] = false;
  }
  else if(raw->header.dwType == RIM_TYPEHID)
  {
    // TODO:
  }
}
