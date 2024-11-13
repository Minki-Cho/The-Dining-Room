#pragma once
#include "vec2.h"
#include "GameObjectTypes.h"
#include "FoodType.h"

#include "../Engine/GameObject.h"
#include "../Engine/Texture.h"

class Food : public GameObject
{
public:
	Food() = default;
	Food(FoodType _type);
	void Draw(mat3<float> TransformMatrix);
	vec2 GetPosition();
	FoodType GetType();
	void SetType(FoodType _type);
	GameObjectType GetObjectType() override { return GameObjectType::Food; }
	std::string GetObjectTypeName() override{ return "Food"; }
	int GetPrice();

	FoodType RandomFood(std::vector<FoodType> const& t);

private:
	vec2 position;
	FoodType type;
	Texture texture;
	int price;
};