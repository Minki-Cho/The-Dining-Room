#include "PickUpWorkBench.h"
#include "../Engine/Engine.h"
#include "Number.h"
#include "Unlock.h"
PickUpWorkBench::PickUpWorkBench(rect3 rect, Player* _player, FoodType _type)
	: WorkBench(rect, _player), type(_type)
{
	food = new Food(type);
	numTex.Load("assets/images/numbers/2r.png");
}

void PickUpWorkBench::Check()
{
	if (this->GetCheck() == true && player->GetIsOnTask() == true)
	{
		if (&player->GetFood() == nullptr)
		{
			if (Engine::GetGSComponent<Unlock>()->GetLettuce() == false && type == FoodType::LETTUCE)
			{
				food->SetType(FoodType::None);
			}
			else if (Engine::GetGSComponent<Unlock>()->GetCheese() == false && type == FoodType::CHEESE)
			{
				food->SetType(FoodType::None);
			}
			else if (Engine::GetGSComponent<Unlock>()->GetTomato() == false && type == FoodType::TOMATO)
			{
				food->SetType(FoodType::None);
			}
			else
			{
				drawNumber = true;
				numPos = GetPosition();
				food->SetType(type);
				Engine::GetGSComponent<Number>()->UpdateNumber(-2);
				player->SetFood(*food);
			}
		}
		this->SetCheckFalse();
	}
}

void PickUpWorkBench::Update([[maybe_unused]] double dt)
{
	deltaTime = dt;
	if (drawNumber == true && timer < 0.9)
	{
		timer += dt;
	}
	else
	{
		drawNumber = false;
		timer = 0;
	}
}

void PickUpWorkBench::Draw()
{
	numPos.y += 20.f * static_cast<float>(deltaTime);
	mat3<float> mat = mat3<float>::build_translation(numPos) * mat3<float>::build_scale(0.5f);
	if (drawNumber == true)
		numTex.Draw(mat);
}
