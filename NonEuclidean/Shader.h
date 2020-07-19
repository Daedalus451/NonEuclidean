#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>

class Shader
{
public:
  Shader(const char* name);
  ~Shader();

  void Use();
  void SetMVP(const float* mvp, const float* mv);

private:
  GLuint LoadShader(const char* fname, GLenum type);

  std::vector<std::string> attribs;
  GLuint vertId = 0;
  GLuint fragId = 0;
  GLuint progId = 0;
  GLuint mvpId = 0;
  GLuint mvId = 0;
};
