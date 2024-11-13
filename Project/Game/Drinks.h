#pragma once
#include "WorkBench.h"
#include "Food.h"
#include "Player.h"
#include "FoodType.h"

class Drinks : public WorkBench
{
private:
	FoodType type;
	Food* food;
	float timer;
	vec2 position, gauge_position;
	Texture* texture;	//drinks
	Texture* bar;
	Texture* gauge;
	bool isDraw = false;
	bool isUpdate = false;
	//bool canGetDrink = false;

	//for gauge
	GLShader shader;
	GLVertexArray gaugeShape;

	//number
	Texture numTex;
	double drawTimer;
	bool drawNumber{ false };
	double deltaTime{ 0 };
	vec2 numPos = GetPosition();
public:
	Drinks(rect3 rect, Player* _player, FoodType _type = FoodType::COKE);
	void Check() override;
	void Update([[maybe_unused]] double dt) override;
	void Draw() override;
	GameObjectType GetObjectType() override { return GameObjectType::WorkBenches; };
	WorkBenchType GetWorkBenchType() override { return WorkBenchType::Drinks; }
	std::string GetObjectTypeName() override { return "Drinks"; }
};
