#include "mat3.h"
#include "Food.h"
#include "Player.h"

#include "../Engine/Engine.h"

#include <stdio.h>

Food::Food(FoodType _type)
{
	type = _type;
	switch (type) {
	case FoodType::BREAD:
		AddGOComponent(new Sprite("assets/images/foods/bread.spt", this));
		break;
	case FoodType::CHEESE:
		AddGOComponent(new Sprite("assets/images/foods/cheese.spt", this));
		break;
	case FoodType::LETTUCE:
		AddGOComponent(new Sprite("assets/images/foods/lettuce.spt", this));
		break;
	case FoodType::PATTY:
		AddGOComponent(new Sprite("assets/images/foods/patty.spt", this));
		break;
	case FoodType::TOMATO:
		AddGOComponent(new Sprite("assets/images/foods/tomato.spt", this));
		break;
	case FoodType::C:
		AddGOComponent(new Sprite("assets/images/foods/burger_cheese.spt", this));
		price = 10;
		break;
	case FoodType::L:
		AddGOComponent(new Sprite("assets/images/foods/burger_lettuce.spt", this));
		price = 8;
		break;
	case FoodType::P:
		AddGOComponent(new Sprite("assets/images/foods/burger_patty.spt", this));
		price = 6;
		break;
	case FoodType::CL:
		AddGOComponent(new Sprite("assets/images/foods/burger_cheese_lettuce.spt", this));
		price = 16;
		break;
	case FoodType::PL:
		AddGOComponent(new Sprite("assets/images/foods/burger_patty_lettuce.spt", this));
		price = 11;
		break;
	case FoodType::CP:
		AddGOComponent(new Sprite("assets/images/foods/burger_cheese_patty.spt", this));
		price = 13;
		break;
	case FoodType::CLP:
		AddGOComponent(new Sprite("assets/images/foods/burger_cheese_lettuce_patty.spt", this));
		price = 18;
		break;
	case FoodType::T:
		AddGOComponent(new Sprite("assets/images/foods/burger_tomato.spt", this));
		price = 9;
		break;
	case FoodType::PT:
		AddGOComponent(new Sprite("assets/images/foods/burger_patty_tomato.spt", this));
		price = 12;
		break;
	case FoodType::LT:
		AddGOComponent(new Sprite("assets/images/foods/burger_tomato_lettuce.spt", this));
		price = 15;
		break;
	case FoodType::CT:
		AddGOComponent(new Sprite("assets/images/foods/burger_cheese_tomato.spt", this));
		price = 17;
		break;
	case FoodType::PLT:
		AddGOComponent(new Sprite("assets/images/foods/burger_lettuce_patty_tomato.spt", this));
		price = 19;
		break;
	case FoodType::PCT:
		AddGOComponent(new Sprite("assets/images/foods/burger_cheese_patty_tomato.spt", this));
		price = 21;
		break;
	case FoodType::LCT:
		AddGOComponent(new Sprite("assets/images/foods/burger_cheese_lettuce_tomato.spt", this));
		price = 23;
		break;
	case FoodType::PLCT:
		AddGOComponent(new Sprite("assets/images/foods/burger_cheese_lettuce_patty_tomato.spt", this));
		price = 24;
		break;

	case FoodType::COKE:
		AddGOComponent(new Sprite("assets/images/foods/coke.spt", this));
		price = 4;
		break;
	case FoodType::FRENCHFRIES:
		AddGOComponent(new Sprite("assets/images/foods/french_fries.spt", this));
		price = 4;
		break;
	case FoodType::ICECREAM:
		AddGOComponent(new Sprite("assets/images/foods/ice_cream.spt", this));
		price = 6;
		break;
	}
}

void Food::Draw(mat3<float> TransformMatrix)
{
	GameObject::Draw(TransformMatrix);
}

vec2 Food::GetPosition()
{
	return position;
}

FoodType Food::GetType()
{
	return type;
}

void Food::SetType(FoodType _type)
{
	type = _type;
}

int Food::GetPrice()
{
	return price;
}

FoodType Food::RandomFood(std::vector<FoodType> const& t)
{
	int r = rand() % t.size();
	return t[r];
}