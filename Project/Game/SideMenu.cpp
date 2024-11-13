#include "SideMenu.h"
#include "Market.h"
#include "Unlock.h"
#include "../Engine/Engine.h"

#include <iostream>

SideMenu::SideMenu() :
	buyIcecream("assets/images/market/buy.png", "assets/images/cursor.png", { 635, 180 })
{
	Merchandise.push_back(Texture("assets/images/market/sidemenu/icecream.png", false));

	buyIcecream.SetIsHighlighted(false);
}


void SideMenu::Update([[maybe_unused]] double dt)
{
	if (Engine::GetGSComponent<Market>()->GetSideMenuDraw() == true)
	{
		SideMenuDraw = true;

		Engine::GetGSComponent<Market>()->SetIngredientDraw(false);
		Engine::GetGSComponent<Market>()->SetSideMenuDraw(true);
		Engine::GetGSComponent<Market>()->SetSkillDraw(false);
	}

	if (SideMenuDraw == true
		&& Engine::GetGSComponent<Market>()->GetIngredientDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSkillDraw() == false)
	{
		
		//buyIcecream button
		if (buyIcecream.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) + 175 < Engine::GetInput().GetMousePos().x + 175
			&& (buyIcecream.GetPosition().x + buyIcecream.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) + 175 > Engine::GetInput().GetMousePos().x + 175
			&& buyIcecream.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (buyIcecream.GetPosition().y + buyIcecream.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			std::cout << "Toamto button is here!" << std::endl;
			buyIcecream.SetIsHighlighted(true);

			if (Engine::GetInput().GetMousePressed() == true)
			{
				if (Engine::GetGSComponent<Unlock>()->GetIcecream() == false)
				{
					Engine::GetLogger().LogDebug("clicked");
					isbuyIcecreamClicked = true;
				}
			}
			else
			{
				isbuyIcecreamClicked = false;
			}
		}
		else
		{
			buyIcecream.SetIsHighlighted(false);
		}
	}
}

void SideMenu::Draw()
{
	if (SideMenuDraw == true && Engine::GetInput().getPause() == false
		&& Engine::GetGSComponent<Market>()->GetIngredientDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSkillDraw() == false)
	{
		Merchandise[0].Draw(mat3<float>::build_translation(vec2(625, 280)));

		if (Engine::GetGSComponent<Unlock>()->GetIcecream() == false)
		{
			buyIcecream.Draw();
		}
	}
}

void SideMenu::Unload()
{
	SideMenuDraw = false;
}
