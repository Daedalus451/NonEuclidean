#include "Level6.h"

#include "Floorplan.h"

void Level6::Load(PObjectVec& objs, PPortalVec& portals, Player& player)
{
  auto floorplan = std::make_shared<Floorplan>();
  objs.push_back(floorplan);
  floorplan->AddPortals(portals);

  player.SetPosition(Vector3(2, GH::PLAYER_HEIGHT, 2));
}
