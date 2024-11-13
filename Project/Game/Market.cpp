#include "Market.h"
#include "Unlock.h"
#include <iostream>
#include "DayByDay.h"
#include "ingredient.h"
#include "SideMenu.h"
#include "Skill.h"

#include "../Engine/Engine.h"

Market::Market()
	: BackGround("assets/images/market/background.png", false),
	ingredient_draw(true), sidemenu_draw(false), skill_draw(false)
{
	//result without highligts
	buttons.push_back(new Button{ "assets/images/market/result.png", "assets/images/cursor.png", {135, 600} });

	//market with highligts
	buttons.push_back(new Button{ "assets/images/market/market_highlight.png", "assets/images/cursor.png", {303, 600} });

	//ingredient - 2(No), 3(Yes)
	buttons.push_back(new Button{ "assets/images/market/ingredient/daybyday_market_ingredient.png", "assets/images/cursor.png", { 165, 510 } });
	buttons.push_back(new Button{ "assets/images/market/ingredient/ingredient_highlight.png", "assets/images/cursor.png", { 165, 510 } });

	//side menu - 4(No), 5(Yes)
	buttons.push_back(new Button{ "assets/images/market/sidemenu/daybyday_market_sidemenu.png", "assets/images/cursor.png", { 165, 455 } });
	buttons.push_back(new Button{ "assets/images/market/sidemenu/daybyday_market_sidemenu_highlight.png", "assets/images/cursor.png", { 165, 455 } });

	//skill - 6(No), 7(Yes)
	buttons.push_back(new Button{ "assets/images/market/skill/daybyday_market_skills.png", "assets/images/cursor.png", { 165, 400 } });
	buttons.push_back(new Button{ "assets/images/market/skill/daybyday_market_skills_highlight.png", "assets/images/cursor.png", { 165, 400 } });
}

void Market::Update([[maybe_unused]] double dt)
{
	if (Engine::GetGSComponent<DayByDay>()->GetMarketDraw() == true)
	{
		Isdraw = true;
	}

	if (Isdraw == true)
	{
		//result Button
		if (buttons[0]->GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (buttons[0]->GetPosition().x + buttons[0]->GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& buttons[0]->GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (buttons[0]->GetPosition().y + buttons[0]->GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			buttons[0]->SetIsHighlighted(true);

			if (Engine::GetInput().GetMousePressed() == true)
			{
				Engine::GetGSComponent<DayByDay>()->SetResultDraw(true);
				Isdraw = false;
			}
		}
		else
		{
			buttons[0]->SetIsHighlighted(false);
		}

		//market Button
		if (buttons[1]->GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (buttons[1]->GetPosition().x + buttons[1]->GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& buttons[1]->GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (buttons[1]->GetPosition().y + buttons[1]->GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			buttons[1]->SetIsHighlighted(true);

			if (Engine::GetInput().GetMousePressed() == true)
			{
				Engine::GetLogger().LogDebug("clicked");
				Engine::GetGSComponent<DayByDay>()->SetResultDraw(false);
				Isdraw = true;
			}
		}
		else
		{
			buttons[1]->SetIsHighlighted(false);
		}

		//ingredients button
		if (buttons[2]->GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (buttons[2]->GetPosition().x + buttons[2]->GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& buttons[2]->GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (buttons[2]->GetPosition().y + buttons[2]->GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			buttons[2]->SetIsHighlighted(true);

			if (Engine::GetInput().GetMousePressed() == true)
			{
				Engine::GetLogger().LogDebug("clicked");

				ingredient_draw = true;
				sidemenu_draw = false;
				skill_draw = false;

				Engine::GetGSComponent<ingredient>()->SetDraw(true);
			}
		}
		else
		{
			buttons[2]->SetIsHighlighted(false);
		}

		//sidemenu button
		if (buttons[4]->GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (buttons[4]->GetPosition().x + buttons[4]->GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& buttons[4]->GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) - 55 < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y) - 55
			&& (buttons[4]->GetPosition().y + buttons[4]->GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) - 55 > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y) - 55)
		{
			buttons[4]->SetIsHighlighted(true);

			if (Engine::GetInput().GetMousePressed() == true)
			{
				Engine::GetLogger().LogDebug("clicked");

				ingredient_draw = false;
				sidemenu_draw = true;
				skill_draw = false;
				
			}
		}
		else
		{
			buttons[4]->SetIsHighlighted(false);
		}


		//skill button
		if (buttons[6]->GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (buttons[6]->GetPosition().x + buttons[6]->GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& buttons[6]->GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) - 110 < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y) - 110
			&& (buttons[6]->GetPosition().y + buttons[6]->GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) - 110 > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y) - 110)
		{
			buttons[6]->SetIsHighlighted(true);

			if (Engine::GetInput().GetMousePressed() == true)
			{
				Engine::GetLogger().LogDebug("clicked");

				ingredient_draw = false;
				sidemenu_draw = false;
				skill_draw = true;

				Engine::GetGSComponent<Skill>()->SetDraw(true);
			}
		}
		else
		{
			buttons[6]->SetIsHighlighted(false);
		}
	}
}

void Market::Draw()
{
	if (Engine::GetInput().getPause() == false && Isdraw == true)
	{
		BackGround.Draw(mat3<float>::build_translation({ 0.f,0.f }));

		buttons[0]->Draw();
		buttons[1]->Draw();

		if (ingredient_draw == true)
		{
			buttons[3]->Draw();
			buttons[4]->Draw();
			buttons[6]->Draw();
		}

		else if (sidemenu_draw == true)
		{
			buttons[2]->Draw();
			buttons[5]->Draw();
			buttons[6]->Draw();
		}

		else if (skill_draw == true)
		{
			buttons[2]->Draw();
			buttons[4]->Draw();
			buttons[7]->Draw();
		}
	}
}

void Market::Unload()
{
	Isdraw = false;
	ingredient_draw = false;
	sidemenu_draw = false;
	skill_draw = false;

	buttons.clear();
}