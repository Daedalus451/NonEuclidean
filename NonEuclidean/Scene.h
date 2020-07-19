#pragma once

#include "Object.h"
#include "Player.h"
#include "Portal.h"

class Scene
{
public:
  virtual ~Scene() = default;

  virtual void Load(PObjectVec& objs, PPortalVec& portals, Player& player) = 0;
  virtual void Unload(){};
};
