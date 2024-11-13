#include "Skill.h"

#include "Market.h"
#include "Unlock.h"
#include "../Engine/Engine.h"
#include <iostream>

Skill::Skill() :
	buydash("assets/images/market/buy.png", "assets/images/cursor.png", { 635, 180 })
{
	Merchandise.push_back(Texture("assets/images/market/skill/dash.png", false));

	buydash.SetIsHighlighted(false);
}

void Skill::Update([[maybe_unused]] double dt)
{
	if (Engine::GetGSComponent<Market>()->GetSkillDraw() == true)
	{
		Skilldraw = true;

		Engine::GetGSComponent<Market>()->SetSideMenuDraw(false);
		Engine::GetGSComponent<Market>()->SetIngredientDraw(false);
	}

	if (Skilldraw == true
		&& Engine::GetGSComponent<Market>()->GetIngredientDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSideMenuDraw() == false)
	{
		//buydash button
		if (buydash.GetPosition().x* (Engine::GetWindow().GetSize().x / 1280.f) + 175 < Engine::GetInput().GetMousePos().x + 175
			&& (buydash.GetPosition().x + buydash.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) + 175 > Engine::GetInput().GetMousePos().x + 175
			&& buydash.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (buydash.GetPosition().y + buydash.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			buydash.SetIsHighlighted(true);

			if (Engine::GetInput().GetMousePressed() == true)
			{
				if (Engine::GetGSComponent<Unlock>()->GetDash() == false)
				{
					Engine::GetLogger().LogDebug("clicked");
					isbuyDashClicked = true;
				}
			}
			else
			{
				isbuyDashClicked = false;
			}
		}
		else
		{
			buydash.SetIsHighlighted(false);
		}
	}

}


void Skill::Draw()
{
	if (Skilldraw == true && Engine::GetInput().getPause() == false
		&& Engine::GetGSComponent<Market>()->GetIngredientDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSideMenuDraw() == false)
	{

		if (Engine::GetGSComponent<Unlock>()->GetDash() == false)
		{
			buydash.Draw();
		}

		Merchandise[0].Draw(mat3<float>::build_translation(vec2(625, 280)));

	}
}

void Skill::Unload()
{
	Skilldraw = false;
}
