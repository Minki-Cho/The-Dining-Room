#pragma once
#include "WorkBench.h"
#include "Player.h"
#include "vec2.h"

class Table : public WorkBench
{
public:
	Table(rect3 rect, Player* _player);
	void Check() override;
	void Update([[maybe_unused]] double dt) override;
	void Draw() override;
	bool GetEmpty();
	void SetEmpty(bool _setValue);
	GameObjectType GetObjectType() override { return GameObjectType::WorkBenches; };
	WorkBenchType GetWorkBenchType() override { return WorkBenchType::Table; }
	std::string GetObjectTypeName() override { return "Table"; }

private:
	bool isEmpty{ true };
	vec2 position{ 0,0 };
	Texture* texturePtr;
};