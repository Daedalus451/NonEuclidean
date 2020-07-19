#include "Level5.h"

#include "Ground.h"
#include "Tunnel.h"

void Level5::Load(PObjectVec& objs, PPortalVec& portals, Player& player)
{
  auto tunnel1 = std::make_shared<Tunnel>(Tunnel::Type::SCALE);
  tunnel1->pos = Vector3(-1.2f, 0, 0);
  tunnel1->scale = Vector3(1, 1, 2.4f);
  objs.push_back(tunnel1);

  auto ground1 = std::make_shared<Ground>();
  ground1->scale *= 1.2f;
  objs.push_back(ground1);

  auto tunnel2 = std::make_shared<Tunnel>(Tunnel::Type::NORMAL);
  tunnel2->pos = Vector3(201.2f, 0, 0);
  tunnel2->scale = Vector3(1, 1, 2.4f);
  objs.push_back(tunnel2);

  auto ground2 = std::make_shared<Ground>();
  ground2->pos = Vector3(200, 0, 0);
  ground2->scale *= 1.2f;
  objs.push_back(ground2);

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

  Portal::Connect(*portal1, *portal2);
  Portal::Connect(*portal3, *portal4);

  auto tunnel3 = std::make_shared<Tunnel>(Tunnel::Type::NORMAL);
  tunnel3->pos = Vector3(-1, 0, -4.2f);
  tunnel3->scale = Vector3(0.25f, 0.25f, 0.6f);
  tunnel3->euler.y = GH::PI / 2;
  objs.push_back(tunnel3);

  player.SetPosition(Vector3(0, GH::PLAYER_HEIGHT, 5));
}
