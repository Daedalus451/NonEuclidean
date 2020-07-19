#pragma once

#include "Scene.h"

class Level4 : public Scene
{
public:
  ~Level4() override = default;

  void Load(PObjectVec& objs, PPortalVec& portals, Player& player) override;
};
