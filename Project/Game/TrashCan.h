#pragma once

#include "WorkBench.h"
#include "Player.h"

class TrashCan : public WorkBench
{
public:
	TrashCan(rect3 rect, Player* _player);
	void Check() override;
	void Update([[maybe_unused]] double dt) override;
	void Draw() override;
	GameObjectType GetObjectType() override { return GameObjectType::WorkBenches; };
	WorkBenchType GetWorkBenchType() override { return WorkBenchType::TrashCan; }
	std::string GetObjectTypeName() override { return "TrashCan"; }

private:
	vec2 position{ 0,0 };
	Texture* texturePtr;
};