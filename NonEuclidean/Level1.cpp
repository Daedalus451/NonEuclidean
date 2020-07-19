#include "Level1.h"

#include "Ground.h"
#include "Tunnel.h"

void Level1::Load(PObjectVec& objs, PPortalVec& portals, Player& player)
{
  auto tunnel1 = std::make_shared<Tunnel>(Tunnel::Type::NORMAL);
  tunnel1->pos = Vector3(-2.4f, 0, -1.8f);
  tunnel1->scale = Vector3(1, 1, 4.8f);
  objs.push_back(tunnel1);

  auto tunnel2 = std::make_shared<Tunnel>(Tunnel::Type::NORMAL);
  tunnel2->pos = Vector3(2.4f, 0, 0);
  tunnel2->scale = Vector3(1, 1, 0.6f);
  objs.push_back(tunnel2);

  auto ground = std::make_shared<Ground>();
  ground->scale *= 1.2f;
  objs.push_back(ground);

  auto portal1 = std::make_shared<Portal>();
  tunnel1->SetDoor1(*portal1);
  portals.push_back(portal1);

  auto portal2 = std::make_shared<Portal>();
  tunnel2->SetDoor1(*portal2);
  portals.push_back(portal2);

  auto portal3 = std::make_shared<Portal>();
  tunnel1->SetDoor2(*portal3);
  portals.push_back(portal3);

  auto portal4 = std::make_shared<Portal>();
  tunnel2->SetDoor2(*portal4);
  portals.push_back(portal4);

  Portal::Connect(portal1, portal2);
  Portal::Connect(portal3, portal4);

  player.SetPosition(Vector3(0, GH::PLAYER_HEIGHT, 5));
}
