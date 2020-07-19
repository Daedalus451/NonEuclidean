#pragma once

#include "Scene.h"

class Level5 : public Scene
{
public:
  ~Level5() override = default;

  void Load(PObjectVec& objs, PPortalVec& portals, Player& player) override;
};
