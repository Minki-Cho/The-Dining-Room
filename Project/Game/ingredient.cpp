#include "ingredient.h"
#include "Market.h"
#include "Unlock.h"
#include "../Engine/Engine.h"

#include <iostream>

ingredient::ingredient() : 
buylettuce("assets/images/market/buy.png", "assets/images/cursor.png", { 390, 180 }),
buytomato("assets/images/market/buy.png", "assets/images/cursor.png", { 635, 180 }),
buycheese("assets/images/market/buy.png", "assets/images/cursor.png", { 880, 180 })
{
	Merchandise.push_back(Texture("assets/images/market/ingredient/lettuce.png", false));
	Merchandise.push_back(Texture("assets/images/market/ingredient/tomato.png", false));
	Merchandise.push_back(Texture("assets/images/market/ingredient/cheese.png", false));

	buylettuce.SetIsHighlighted(false);
	buytomato.SetIsHighlighted(false);
	buycheese.SetIsHighlighted(false);
}


void ingredient::Update([[maybe_unused]]double dt)
{
	if (Engine::GetGSComponent<Market>()->GetIngredientDraw() == true)
	{
		IngredientsDraw = true;

		Engine::GetGSComponent<Market>()->SetIngredientDraw(true);
		Engine::GetGSComponent<Market>()->SetSideMenuDraw(false);
		Engine::GetGSComponent<Market>()->SetSkillDraw(false);
	}

	if (IngredientsDraw == true
		&& Engine::GetGSComponent<Market>()->GetSideMenuDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSkillDraw() == false)
	{
		//buylettece button
		if (buylettuce.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) - 80 < Engine::GetInput().GetMousePos().x - 80
			&& (buylettuce.GetPosition().x + buylettuce.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) - 80 > Engine::GetInput().GetMousePos().x - 80
			&& buylettuce.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (buylettuce.GetPosition().y + buylettuce.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			std::cout << "here" << std::endl;
			buylettuce.SetIsHighlighted(true);

			if (Engine::GetInput().GetMousePressed() == true)
			{
				if (Engine::GetGSComponent<Unlock>()->GetLettuce() == false)
				{
					Engine::GetLogger().LogDebug("clicked");
					isbuyLettuceClicked = true;
				}
			}
			else
			{
				isbuyLettuceClicked = false;
			}
		}
		else
		{
			buylettuce.SetIsHighlighted(false);
		}

		//buytomato button
		if (buytomato.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) + 175 < Engine::GetInput().GetMousePos().x + 175
			&& (buytomato.GetPosition().x + buytomato.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) + 175 > Engine::GetInput().GetMousePos().x + 175
			&& buytomato.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (buytomato.GetPosition().y + buytomato.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			std::cout << "Toamto button is here!" << std::endl;
			buytomato.SetIsHighlighted(true);

			if (Engine::GetInput().GetMousePressed() == true)
			{
				if (Engine::GetGSComponent<Unlock>()->GetTomato() == false)
				{
					Engine::GetLogger().LogDebug("clicked");
					isbuyTomatoClicked = true;
				}
			}
			else
			{
				isbuyTomatoClicked = false;
			}
		}
		else
		{
			buytomato.SetIsHighlighted(false);
		}

		//buycheese button
		if (buycheese.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) + 80 < Engine::GetInput().GetMousePos().x + 80
			&& (buycheese.GetPosition().x + buycheese.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) + 80 > Engine::GetInput().GetMousePos().x + 80
			&& buycheese.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (buycheese.GetPosition().y + buycheese.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			buycheese.SetIsHighlighted(true);

			if (Engine::GetInput().GetMousePressed() == true)
			{
				if (Engine::GetGSComponent<Unlock>()->GetCheese() == false)
				{
					Engine::GetLogger().LogDebug("clicked");
					isbuyCheeseClicked = true;
				}
			}
			else
			{
				isbuyCheeseClicked = false;
			}
		}
		else
		{
			buycheese.SetIsHighlighted(false);
		}
	}
}

void ingredient::Draw()
{
	if (IngredientsDraw == true && Engine::GetInput().getPause() == false
		&& Engine::GetGSComponent<Market>()->GetSideMenuDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSkillDraw() == false)
	{
		Merchandise[0].Draw(mat3<float>::build_translation(vec2(380, 280)));
		Merchandise[1].Draw(mat3<float>::build_translation(vec2(625, 280)));
		Merchandise[2].Draw(mat3<float>::build_translation(vec2(870, 280)));

		if (Engine::GetGSComponent<Unlock>()->GetLettuce() == false)
		{
			buylettuce.Draw();
		}
		if (Engine::GetGSComponent<Unlock>()->GetTomato() == false)
		{
			buytomato.Draw();
		}
		if (Engine::GetGSComponent<Unlock>()->GetCheese() == false)
		{
			buycheese.Draw();
		}
	}
}

void ingredient::Unload()
{
	IngredientsDraw = false;
}
