#pragma once

#include "Scene.h"

class Level2 : public Scene
{
public:
  Level2(int rooms)
  : num_rooms(rooms)
  {
  }

  ~Level2() override = default;

  void Load(PObjectVec& objs, PPortalVec& portals, Player& player) override;

private:
  int num_rooms = 0;
};
