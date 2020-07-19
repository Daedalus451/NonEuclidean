#pragma once

#include "Scene.h"

class Level6 : public Scene
{
public:
  ~Level6() override = default;

  void Load(PObjectVec& objs, PPortalVec& portals, Player& player) override;
};
