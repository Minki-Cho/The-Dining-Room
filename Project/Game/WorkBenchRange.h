#pragma once
#include "vec2.h"
#include "GameObjectTypes.h"
#include "WorkBench.h"
#include "Direction.h"

#include "../Engine/GameObject.h"
#include "../Engine/Collision.h"

class Player;

class WorkBenchRange : public GameObject
{
protected:
	rect3 rect;
	vec2 size;
	Direction direction;
	WorkBench* workbench;

public:
	WorkBenchRange(WorkBench* _workbench, Direction _direction);
	vec2 GetSize();
	void Update(double dt) override;
	bool CanCollideWith(GameObjectType objectBType) override;
	void ResolveCollision(GameObject* objectB) override;
	GameObjectType GetObjectType() override { return GameObjectType::WorkBenchRange; };
	std::string GetObjectTypeName() override { return "WorkBenchRange"; }
private:

};