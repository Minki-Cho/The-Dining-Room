#pragma once
#include "WorkBench.h"
#include "Food.h"
#include "Player.h"
#include "../Engine/Engine.h"

class PickUpWorkBench : public WorkBench
{
private:
	FoodType type;
	Food* food;

	Texture numTex;
	double timer;
	bool drawNumber{ false };
	double deltaTime{ 0 };
	vec2 numPos = GetPosition();
public:
	PickUpWorkBench(rect3 rect, Player* _player, FoodType _type);
	void Check() override;
	void Update([[maybe_unused]] double dt) override;
	void Draw() override;
	GameObjectType GetObjectType() override { return GameObjectType::WorkBenches; };
	WorkBenchType GetWorkBenchType() override { return WorkBenchType::PickUp; }
	std::string GetObjectTypeName() override { return "PickUp WorkBench"; }
};
