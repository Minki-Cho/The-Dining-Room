#include "Counter.h"
#include "Reputation.h"

Counter::Counter(rect3 rect, Player* _player)
	: WorkBench(rect, _player)
{
	givenMainFood = new Food;
	givenSideFood = new Food;
	givenMainFood->SetType(FoodType::Count);
	givenSideFood->SetType(FoodType::Count);
}

void Counter::Check()
{
	if (this->GetCheck() == true && player->GetIsOnTask() == true && player->IsFoodOnHand() == true)
	{
		if (count < 2)
		{
			if (player->GetFood().GetType() >= FoodType::P && player->GetFood().GetType() <= FoodType::PLCT)
			{
				if (givenMainFood->GetType() == FoodType::Count)
				{
					givenMainFood->SetType(player->GetFood().GetType());
					player->SetLastOrder(player->GetFood().GetType());
					player->SetFoodToNull();
					player->SetIsSuccess();
					player->SetCanDelivery(false);
					count++;
				}
			}
			else if (player->GetFood().GetType() >= FoodType::COKE && player->GetFood().GetType() < FoodType::Count)
			{
				if (givenSideFood->GetType() == FoodType::Count)
				{
					givenSideFood->SetType(player->GetFood().GetType());
					player->SetLastOrder(player->GetFood().GetType());
					player->SetFoodToNull();
					player->SetIsSuccess();
					player->SetCanDelivery(false);
					count++;
				}
			}
		}
		this->SetCheckFalse();
	}
}

void Counter::Update([[maybe_unused]] double dt)
{
}

void Counter::Draw()
{
}