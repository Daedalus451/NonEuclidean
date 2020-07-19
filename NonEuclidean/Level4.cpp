#include "Level4.h"

#include "Ground.h"
#include "Tunnel.h"

void Level4::Load(PObjectVec& objs, PPortalVec& portals, Player& player)
{
  auto tunnel1 = std::make_shared<Tunnel>(Tunnel::Type::SLOPE);
  tunnel1->pos = Vector3(0, 0, 0);
  tunnel1->scale = Vector3(1, 1, 5);
  tunnel1->euler.y = GH::PI;
  objs.push_back(tunnel1);

  auto ground1 = std::make_shared<Ground>(true);
  ground1->scale *= Vector3(1, 2, 1);
  objs.push_back(ground1);

  auto tunnel2 = std::make_shared<Tunnel>(Tunnel::Type::SLOPE);
  tunnel2->pos = Vector3(200, 0, 0);
  tunnel2->scale = Vector3(1, 1, 5);
  objs.push_back(tunnel2);

  auto ground2 = std::make_shared<Ground>(true);
  ground2->pos = Vector3(200, 0, 0);
  ground2->scale *= Vector3(1, 2, 1);
  ground2->euler.y = GH::PI;
  objs.push_back(ground2);

  auto portal1 = std::make_shared<Portal>();
  tunnel1->SetDoor1(*portal1);
  portals.push_back(portal1);

  auto portal2 = std::make_shared<Portal>();
  tunnel1->SetDoor2(*portal2);
  portals.push_back(portal2);

  auto portal3 = std::make_shared<Portal>();
  tunnel2->SetDoor1(*portal3);
  portal3->euler.y -= GH::PI;
  portals.push_back(portal3);

  auto portal4 = std::make_shared<Portal>();
  tunnel2->SetDoor2(*portal4);
  portal4->euler.y -= GH::PI;
  portals.push_back(portal4);

  Portal::Connect(portal1, portal4);
  Portal::Connect(portal2, portal3);

  player.SetPosition(Vector3(0, GH::PLAYER_HEIGHT - 2, 8));
}
