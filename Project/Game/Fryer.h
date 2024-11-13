#pragma once
#include "WorkBench.h"
#include "Food.h"
#include "Player.h"
#include "FoodType.h"

class Fryer : public WorkBench
{
private:
	FoodType type;
	Food* food;
	float timer;
	vec2 position, gauge_position;
	Texture* texture;	//fryer
	Texture* bar;
	Texture* gauge;
	bool isDraw = false;
	bool isUpdate = false;

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
	Fryer(rect3 rect, Player* _player, FoodType _type = FoodType::FRENCHFRIES);
	void Check() override;
	void Update([[maybe_unused]] double dt) override;
	void Draw() override;
	GameObjectType GetObjectType() override { return GameObjectType::WorkBenches; };
	WorkBenchType GetWorkBenchType() override { return WorkBenchType::Fryer; }
	std::string GetObjectTypeName() override { return "Fryer"; }
};
