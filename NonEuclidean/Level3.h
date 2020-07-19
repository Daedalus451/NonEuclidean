#pragma once

#include "Scene.h"

class Level3 : public Scene
{
public:
  ~Level3() override = default;

  void Load(PObjectVec& objs, PPortalVec& portals, Player& player) override;
};
