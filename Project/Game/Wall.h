#pragma once
#include <string>
#include "GameObjectTypes.h"
#include "..\Engine\GameObject.h"

struct rect3;

class Wall : public GameObject
{
public:
    Wall(rect3 rect);
    std::string GetObjectTypeName() override { return "Wall"; }
    GameObjectType GetObjectType() override { return GameObjectType::Wall; }
};