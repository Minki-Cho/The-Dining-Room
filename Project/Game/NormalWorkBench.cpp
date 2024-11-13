#include "NormalWorkBench.h"
void NormalWorkBench::Check()
{
	if (this->GetCheck() == true && player->GetIsOnTask() == true)
	{
		// put down | pick up
		if (&player->GetFood() != nullptr && food == nullptr)
		{
			food = &player->GetFood();
			player->SetFoodToNull();
		}
		else if (&player->GetFood() == nullptr && food != nullptr)
		{
			player->SetFood(*food);
			food = nullptr;
		}

		// combine the ingredients
		if (&player->GetFood() != nullptr && food != nullptr)
		{
			switch (player->GetFood().GetType())
			{
			case FoodType::BREAD:
				
				switch (food->GetType())
				{
				case FoodType::CHEESE:
					food = nullptr;
					food = new Food(FoodType::C);
					player->SetFoodToNull();
					break;
				case FoodType::LETTUCE:
					food = nullptr;
					food = new Food(FoodType::L);
					player->SetFoodToNull();
					break;
				case FoodType::PATTY:
					food = nullptr;
					food = new Food(FoodType::P);
					player->SetFoodToNull();
					break;
				case FoodType::TOMATO:
					food = nullptr;
					food = new Food(FoodType::T);
					player->SetFoodToNull();
					break;
				default:
					break;
				}
				break;

			case FoodType::CHEESE:
				switch (food->GetType())
				{
				case FoodType::BREAD:
					food = nullptr;
					food = new Food(FoodType::C);
					player->SetFoodToNull();
					break;
				case FoodType::P:
					food = nullptr;
					food = new Food(FoodType::CP);
					player->SetFoodToNull();
					break;
				case FoodType::L:
					food = nullptr;
					food = new Food(FoodType::CL);
					player->SetFoodToNull();
					break;
				case FoodType::T:
					food = nullptr;
					food = new Food(FoodType::CT);
					player->SetFoodToNull();
					break;
				case FoodType::PL:
					food = nullptr;
					food = new Food(FoodType::CLP);
					player->SetFoodToNull();
					break;
				case FoodType::PT:
					food = nullptr;
					food = new Food(FoodType::PCT);
					player->SetFoodToNull();
					break;
				case FoodType::LT:
					food = nullptr;
					food = new Food(FoodType::LCT);
					player->SetFoodToNull();
					break;
				case FoodType::PLT:
					food = nullptr;
					food = new Food(FoodType::PLCT);
					player->SetFoodToNull();
					break;
				default:
					break;
				}
				break;

			case FoodType::PATTY:
				switch (food->GetType())
				{
				case FoodType::BREAD:
					food = nullptr;
					food = new Food(FoodType::P);
					player->SetFoodToNull();
					break;
				case FoodType::C:
					food = nullptr;
					food = new Food(FoodType::CP);
					player->SetFoodToNull();
					break;
				case FoodType::L:
					food = nullptr;
					food = new Food(FoodType::PL);
					player->SetFoodToNull();
					break;
				case FoodType::T:
					food = nullptr;
					food = new Food(FoodType::PT);
					player->SetFoodToNull();
					break;
				case FoodType::CL:
					food = nullptr;
					food = new Food(FoodType::CLP);
					player->SetFoodToNull();
					break;
				case FoodType::LT:
					food = nullptr;
					food = new Food(FoodType::PLT);
					player->SetFoodToNull();
					break;
				case FoodType::CT:
					food = nullptr;
					food = new Food(FoodType::PCT);
					player->SetFoodToNull();
					break;
				case FoodType::LCT:
					food = nullptr;
					food = new Food(FoodType::PLCT);
					player->SetFoodToNull();
					break;
				default:
					break;
				}
				break;

			case FoodType::LETTUCE:
				switch (food->GetType())
				{
				case FoodType::BREAD:
					food = nullptr;
					food = new Food(FoodType::L);
					player->SetFoodToNull();
					break;
				case FoodType::C:
					food = nullptr;
					food = new Food(FoodType::CL);
					player->SetFoodToNull();
					break;
				case FoodType::P:
					food = nullptr;
					food = new Food(FoodType::PL);
					player->SetFoodToNull();
					break;
				case FoodType::T:
					food = nullptr;
					food = new Food(FoodType::LT);
					player->SetFoodToNull();
					break;
				case FoodType::CP:
					food = nullptr;
					food = new Food(FoodType::CLP);
					player->SetFoodToNull();
					break;
				case FoodType::CT:
					food = nullptr;
					food = new Food(FoodType::LCT);
					player->SetFoodToNull();
					break;
				case FoodType::PT:
					food = nullptr;
					food = new Food(FoodType::PLT);
					player->SetFoodToNull();
					break;
				case FoodType::PCT:
					food = nullptr;
					food = new Food(FoodType::PLCT);
					player->SetFoodToNull();
					break;
				default:
					break;
				}
				break;

			case FoodType::TOMATO:
				switch (food->GetType())
				{
				case FoodType::BREAD:
					food = nullptr;
					food = new Food(FoodType::T);
					player->SetFoodToNull();
					break;
				case FoodType::C:
					food = nullptr;
					food = new Food(FoodType::CT);
					player->SetFoodToNull();
					break;
				case FoodType::L:
					food = nullptr;
					food = new Food(FoodType::LT);
					player->SetFoodToNull();
					break;
				case FoodType::P:
					food = nullptr;
					food = new Food(FoodType::PT);
					player->SetFoodToNull();
					break;
				case FoodType::CP:
					food = nullptr;
					food = new Food(FoodType::PCT);
					player->SetFoodToNull();
					break;
				case FoodType::CL:
					food = nullptr;
					food = new Food(FoodType::LCT);
					player->SetFoodToNull();
					break;
				case FoodType::PL:
					food = nullptr;
					food = new Food(FoodType::PLT);
					player->SetFoodToNull();
					break;
				case FoodType::CLP:
					food = nullptr;
					food = new Food(FoodType::PLCT);
					player->SetFoodToNull();
					break;
				default:
					break;
				}
				break;

			default:
				break;
			}
		}
	}
}

void NormalWorkBench::Draw()
{
	if (food != nullptr)
	{
		food->Draw(mat3<float>::build_translation(vec2{ rect.point1.x + 25, rect.point1.y + 25 }));
	}
}

void NormalWorkBench::Update([[maybe_unused]] double dt)
{
}

void NormalWorkBench::RemoveFood()
{
	delete food;
}

void NormalWorkBench::SetEmpty()
{
	if (food != nullptr)
	{
		food = nullptr;
	}
}