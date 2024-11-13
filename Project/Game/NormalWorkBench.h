#pragma once
#include "WorkBench.h"
#include "Food.h"
#include "Player.h"

class NormalWorkBench : public WorkBench
{
private:
	Food* food = nullptr;

public:
	NormalWorkBench(rect3 rect, Player* _player) : WorkBench(rect, _player) {};
	void Check() override;
	void Update([[maybe_unused]] double dt) override;
	void Draw() override;
	void RemoveFood();
	void SetEmpty();
	GameObjectType GetObjectType() override { return GameObjectType::WorkBenches; };
	WorkBenchType GetWorkBenchType() override { return WorkBenchType::Normal; }
	std::string GetObjectTypeName() override { return "Normal WorkBench"; }
};