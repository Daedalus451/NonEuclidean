#include "Level3.h"

#include "Ground.h"
#include "Pillar.h"
#include "PillarRoom.h"
#include "Statue.h"

void Level3::Load(PObjectVec& objs, PPortalVec& portals, Player& player)
{
  // Room 1
  auto pillar1 = std::make_shared<Pillar>();
  objs.push_back(pillar1);

  auto pillarRoom1 = std::make_shared<PillarRoom>();
  objs.push_back(pillarRoom1);

  auto ground1 = std::make_shared<Ground>();
  ground1->scale *= 2.0f;
  objs.push_back(ground1);

  auto statue1 = std::make_shared<Statue>("teapot.obj");
  statue1->pos = Vector3(0, 0.5f, 9);
  statue1->scale = Vector3(0.5f);
  statue1->euler.y = GH::PI / 2;
  objs.push_back(statue1);

  // Room 2
  auto pillar2 = std::make_shared<Pillar>();
  pillar2->pos = Vector3(200, 0, 0);
  objs.push_back(pillar2);

  auto pillarRoom2 = std::make_shared<PillarRoom>();
  pillarRoom2->pos = Vector3(200, 0, 0);
  objs.push_back(pillarRoom2);

  auto ground2 = std::make_shared<Ground>();
  ground2->pos = Vector3(200, 0, 0);
  ground2->scale *= 2.0f;
  objs.push_back(ground2);

  auto statue2 = std::make_shared<Statue>("bunny.obj");
  statue2->pos = Vector3(200, -0.4f, 9);
  statue2->scale = Vector3(14.0f);
  statue2->euler.y = GH::PI;
  objs.push_back(statue2);

  // Room 3
  auto pillar3 = std::make_shared<Pillar>();
  pillar3->pos = Vector3(400, 0, 0);
  objs.push_back(pillar3);

  auto pillarRoom3 = std::make_shared<PillarRoom>();
  pillarRoom3->pos = Vector3(400, 0, 0);
  objs.push_back(pillarRoom3);

  auto ground3 = std::make_shared<Ground>();
  ground3->pos = Vector3(400, 0, 0);
  ground3->scale *= 2.0f;
  objs.push_back(ground3);

  auto statue3 = std::make_shared<Statue>("suzanne.obj");
  statue3->pos = Vector3(400, 0.9f, 9);
  statue3->scale = Vector3(1.2f);
  statue3->euler.y = GH::PI;
  objs.push_back(statue3);

  // Portals
  auto portal1 = std::make_shared<Portal>();
  pillarRoom1->SetPortal(*portal1);
  portals.push_back(portal1);

  auto portal2 = std::make_shared<Portal>();
  pillarRoom2->SetPortal(*portal2);
  portals.push_back(portal2);

  auto portal3 = std::make_shared<Portal>();
  pillarRoom3->SetPortal(*portal3);
  portals.push_back(portal3);

  Portal::Connect(portal1->front, portal2->back);
  Portal::Connect(portal2->front, portal3->back);
  Portal::Connect(portal3->front, portal1->back);

  player.SetPosition(Vector3(0, GH::PLAYER_HEIGHT, 3));
}
