#pragma once
#include "vec2.h"
#include "GameObjectTypes.h"

#include "../Engine/GameObject.h"
#include "../Engine/Collision.h"

class Player;

class WorkBench : public GameObject
{
protected:
	rect3 rect;
	vec2 position;	//bottom left
	vec2 size;
	bool check{ false };
	Player* player;

public:
	WorkBench(rect3 _rect, Player* _player) : player(_player), rect(_rect), GameObject(vec2{ 0,0 })
	{
		AddGOComponent(new RectCollision(rect, this));
		position = vec2{ rect.point1.x, rect.point1.y };
		size = vec2{ rect.Size().width, rect.Size().height };
	};

	void SetCheckTrue() { check = true; };
	void SetCheckFalse() { check = false; };
	rect3 GetRect() { return rect; };
	vec2 GetPosition() { return position; };
	vec2 GetSize() { return size; };
	bool GetCheck() { return check; };
	virtual void Check() = 0;
	virtual void Update(double dt) = 0;
	virtual void Draw() = 0;
	GameObjectType GetObjectType() override { return GameObjectType::WorkBenches; };
	virtual WorkBenchType GetWorkBenchType() = 0;
	std::string GetObjectTypeName() override { return "Default WorkBench"; }
};