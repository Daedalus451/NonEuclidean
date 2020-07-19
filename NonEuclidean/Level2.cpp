#include "Level2.h"

#include "House.h"

void Level2::Load(PObjectVec& objs, PPortalVec& portals, Player& player)
{
  auto house1 = std::make_shared<House>("three_room.bmp");
  house1->pos = Vector3(0, 0, -20);
  objs.push_back(house1);

  std::shared_ptr<House> house2;
  if(num_rooms > 4)
  {
    house2 = std::make_shared<House>("three_room2.bmp");
    house2->pos = Vector3(200, 0, -20);
    objs.push_back(house2);
  }

  if(num_rooms == 1)
  {
    auto portal1 = std::make_shared<Portal>();
    house1->SetDoor1(*portal1);
    portals.push_back(portal1);

    auto portal2 = std::make_shared<Portal>();
    house1->SetDoor4(*portal2);
    portals.push_back(portal2);

    Portal::Connect(portal1, portal2);
  }
  else if(num_rooms == 2)
  {
    auto portal1 = std::make_shared<Portal>();
    house1->SetDoor2(*portal1);
    portals.push_back(portal1);

    auto portal2 = std::make_shared<Portal>();
    house1->SetDoor4(*portal2);
    portals.push_back(portal2);

    Portal::Connect(portal1, portal2);
  }
  else if(num_rooms == 3)
  {
    auto portal1 = std::make_shared<Portal>();
    house1->SetDoor3(*portal1);
    portals.push_back(portal1);

    auto portal2 = std::make_shared<Portal>();
    house1->SetDoor4(*portal2);
    portals.push_back(portal2);

    Portal::Connect(portal1, portal2);
  }
  else if(num_rooms == 4)
  {
  }
  else if(num_rooms == 5)
  {
    auto portal1 = std::make_shared<Portal>();
    house1->SetDoor4(*portal1);
    portals.push_back(portal1);

    auto portal2 = std::make_shared<Portal>();
    house2->SetDoor2(*portal2);
    portals.push_back(portal2);

    auto portal3 = std::make_shared<Portal>();
    house2->SetDoor1(*portal3);
    portals.push_back(portal3);

    Portal::Connect(portal1->front, portal2->back);
    Portal::Connect(portal2->front, portal3->back);
    Portal::Connect(portal3->front, portal1->back);
  }
  else if(num_rooms == 6)
  {
    auto portal1 = std::make_shared<Portal>();
    house1->SetDoor4(*portal1);
    portals.push_back(portal1);

    auto portal2 = std::make_shared<Portal>();
    house2->SetDoor3(*portal2);
    portals.push_back(portal2);

    auto portal3 = std::make_shared<Portal>();
    house2->SetDoor1(*portal3);
    portals.push_back(portal3);

    Portal::Connect(portal1->front, portal2->back);
    Portal::Connect(portal2->front, portal3->back);
    Portal::Connect(portal3->front, portal1->back);
  }

  player.SetPosition(Vector3(3, GH::PLAYER_HEIGHT, 3));
}
