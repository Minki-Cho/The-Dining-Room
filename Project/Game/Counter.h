#pragma once
#include "WorkBench.h"
#include "FoodType.h"
#include "Player.h"

inline std::vector<FoodType> orderList = {};

class Counter : public WorkBench
{
private:
	Food* givenMainFood;
	Food* givenSideFood;
	unsigned int count{ 0 };
public:
	Counter(rect3 rect, Player* _player);
	void Check() override;
	void Update([[maybe_unused]] double dt) override;
	void Draw() override;
	Food getGivenFood1()
	{
		return givenMainFood->GetType();
	};
	Food getGivenFood2()
	{
		return givenSideFood->GetType();
	};
	unsigned int getCount() { return count; };
	void setCount()
	{
		givenMainFood->SetType(FoodType::Count);
		givenSideFood->SetType(FoodType::Count);
		count = 0;
	};
	GameObjectType GetObjectType() override { return GameObjectType::WorkBenches; };
	WorkBenchType GetWorkBenchType() override { return WorkBenchType::Counter; }
	std::string GetObjectTypeName() override { return "Counter"; }
};
