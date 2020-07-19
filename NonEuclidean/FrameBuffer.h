#pragma once

#include "Camera.h"
#include <GL/glew.h>

// Forward declaration
class Portal;

class FrameBuffer
{
public:
  FrameBuffer();

  void Render(const Camera& cam, GLuint curFBO, const Portal* skipPortal);
  void Use();

private:
  GLuint texId = 0;
  GLuint fbo = 0;
  GLuint renderBuf = 0;
};
