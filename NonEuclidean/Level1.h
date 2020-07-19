#pragma once

#include "Scene.h"

class Level1 : public Scene
{
public:
  ~Level1() override = default;

  void Load(PObjectVec& objs, PPortalVec& portals, Player& player) override;
};
