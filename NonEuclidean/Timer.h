#pragma once

#include <SDL2/SDL.h>

class Timer
{
public:
  Timer()
  {
    frequency = SDL_GetPerformanceFrequency();
  }

  void Start()
  {
    t1 = SDL_GetPerformanceCounter();
  }

  float Stop()
  {
    t2 = SDL_GetPerformanceCounter();
    return static_cast<float>(t2 - t1) / frequency;
  }

  int64_t GetTicks()
  {
    t2 = SDL_GetPerformanceCounter();
    return t2;
  }

  int64_t SecondsToTicks(float s)
  {
    return static_cast<int64_t>(static_cast<float>(frequency) * s);
  }

  float StopStart()
  {
    const float result = Stop();
    t1 = t2;
    return result;
  }

private:
  int64_t frequency = 0; // ticks per second
  int64_t t1 = 0; // ticks
  int64_t t2 = 0;
};
