#include "Unlock.h"
#include "../Engine/Engine.h"
#include "Settings.h"
#include "Market.h"
#include "Number.h"
#include "Unlock.h"
#include "DayByDay.h"
#include "../Engine/fmod-sound.h"

#include "ingredient.h"
#include "SideMenu.h"
#include "Skill.h"

Unlock::Unlock()
{

}

void Unlock::Load(const std::filesystem::path& texturePath)
{
	texture.push_back({ Engine::GetTextureManager().Load(texturePath, false) });
}

void Unlock::Update(double /*dt*/)
{
	if (Engine::GetGSComponent<ingredient>()->GetisLettuceClicked() == true && Engine::GetGSComponent<Number>()->GetNumber() < 31 )
	{
		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Beep), false);
	}
	else if (Engine::GetGSComponent<ingredient>()->GetisTomatoClicked() == true && Engine::GetGSComponent<Number>()->GetNumber() < 46)
	{
		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Beep), false);
	}
	else if (Engine::GetGSComponent<ingredient>()->GetisCheeseeClicked() == true && Engine::GetGSComponent<Number>()->GetNumber() < 61 )
	{
		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Beep), false);
	}
	else if (Engine::GetGSComponent<SideMenu>()->GetisIcecreamClicked() == true && Engine::GetGSComponent<Number>()->GetNumber() < 61)
	{
		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Beep), false);
	}
	else if (Engine::GetGSComponent<Skill>()->GetisDashClicked() == true && Engine::GetGSComponent<Number>()->GetNumber() < 21)
	{
		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Beep), false);
	}

	//lettuce
	if (Engine::GetGSComponent<Number>()->GetNumber() > 30)
	{
		if (LettuceLocked == true)
		{
			if (Engine::GetGSComponent<ingredient>()->GetisLettuceClicked() == true)
			{
				Engine::GetGSComponent<Number>()->UpdateNumber(-30);
				isLettuce = true;
				LettuceLocked = false;
				UnlockLettuce = true;
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Buy), false);
			}
		}
	}

	//tomato
	if (Engine::GetGSComponent<Number>()->GetNumber() > 45 /*&& Engine::GetGSComponent<Number>()->GetNumber() < 100*/)
	{
		if (TomatoLocked == true)
		{
			if (Engine::GetGSComponent<ingredient>()->GetisTomatoClicked() == true)
			{
				Engine::GetGSComponent<Number>()->UpdateNumber(-45);
				isTomato = true;
				TomatoLocked = false;
				UnlockTomato = true;
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Buy), false);
			}
		}

	}

	//cheese
	if (Engine::GetGSComponent<Number>()->GetNumber() > 60)
	{
		if (CheeseLocked == true)
		{
			if (Engine::GetGSComponent<ingredient>()->GetisCheeseeClicked() == true)
			{
				Engine::GetGSComponent<Number>()->UpdateNumber(-60);
				isCheese = true;
				CheeseLocked = false;
				UnlockCheese = true;
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Buy), false);
			}
		}
	}

	//ice cream
	if (Engine::GetGSComponent<Number>()->GetNumber() > 20 /*&& Engine::GetGSComponent<Number>()->GetNumber() < 100*/)
	{
		if (IcecreamLocked == true)
		{
			if (Engine::GetGSComponent<SideMenu>()->GetisIcecreamClicked() == true)
			{
				Engine::GetGSComponent<Number>()->UpdateNumber(-20);
				isIcecream = true;
				IcecreamLocked = false;
				UnlockIcecream = true;
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Buy), false);
			}
		}
	}

	if (Engine::GetGSComponent<Number>()->GetNumber() > 20 /*&& Engine::GetGSComponent<Number>()->GetNumber() < 100*/)
	{
		if (DashLocked == true)
		{
			if (Engine::GetGSComponent<Skill>()->GetisDashClicked() == true)
			{
				Engine::GetGSComponent<Number>()->UpdateNumber(-20);
				isDash = true;
				DashLocked = false;
				UnlockDash = true;
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Buy), false);
			}
		}
	}

}

void Unlock::Draw()
{
	//locked ingredients
	if (Engine::GetGSComponent<Number>()->GetNumber() < 30
		&& Engine::GetGSComponent<DayByDay>()->GetDrawbool() == true
		&& Engine::GetGSComponent<Market>()->GetIsDraw() == true
		&& Engine::GetGSComponent<Market>()->GetIngredientDraw() == true
		&& Engine::GetGSComponent<Market>()->GetSideMenuDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSkillDraw() == false
		&& LettuceLocked == true && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		texture[0].texturePtr->Draw(mat3<float>::build_translation(390, 500) * mat3<float>::build_scale(1.5));
	}
	if (Engine::GetGSComponent<Number>()->GetNumber() < 45
		&& Engine::GetGSComponent<DayByDay>()->GetDrawbool() == true
		&& Engine::GetGSComponent<Market>()->GetIsDraw() == true
		&& Engine::GetGSComponent<Market>()->GetIngredientDraw() == true
		&& Engine::GetGSComponent<Market>()->GetSideMenuDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSkillDraw() == false
		&& TomatoLocked == true && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		texture[0].texturePtr->Draw(mat3<float>::build_translation(635, 500) * mat3<float>::build_scale(1.5));
	}
	if (Engine::GetGSComponent<Number>()->GetNumber() < 60 
		&& Engine::GetGSComponent<DayByDay>()->GetDrawbool() == true
		&& Engine::GetGSComponent<Market>()->GetIsDraw() == true
		&& Engine::GetGSComponent<Market>()->GetIngredientDraw() == true
		&& Engine::GetGSComponent<Market>()->GetSideMenuDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSkillDraw() == false
		&& CheeseLocked == true && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		texture[0].texturePtr->Draw(mat3<float>::build_translation(880, 500) * mat3<float>::build_scale(1.5));
	}

	//locked sidemenu
	if (Engine::GetGSComponent<Number>()->GetNumber() < 20
		&& Engine::GetGSComponent<DayByDay>()->GetDrawbool() == true
		&& Engine::GetGSComponent<Market>()->GetIsDraw() == true
		&& Engine::GetGSComponent<Market>()->GetIngredientDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSideMenuDraw() == true
		&& Engine::GetGSComponent<Market>()->GetSkillDraw() == false
		&& IcecreamLocked == true && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		texture[0].texturePtr->Draw(mat3<float>::build_translation(635, 500) * mat3<float>::build_scale(1.5));
	}

	//locked skills
	if (Engine::GetGSComponent<Number>()->GetNumber() < 20
		&& Engine::GetGSComponent<DayByDay>()->GetDrawbool() == true
		&& Engine::GetGSComponent<Market>()->GetIsDraw() == true
		&& Engine::GetGSComponent<Market>()->GetIngredientDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSideMenuDraw() == false
		&& Engine::GetGSComponent<Market>()->GetSkillDraw() == true
		&& DashLocked == true && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		texture[0].texturePtr->Draw(mat3<float>::build_translation(635, 500) * mat3<float>::build_scale(1.5));
	}

	//ingame 
	if (LettuceLocked == true && Engine::GetGSComponent<DayByDay>()->getIsDraw() == false && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		texture[0].texturePtr->Draw(mat3<float>::build_translation(1220, 108));
	}
	if (CheeseLocked == true && Engine::GetGSComponent<DayByDay>()->getIsDraw() == false && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		texture[0].texturePtr->Draw(mat3<float>::build_translation(1220, 155));
	}
	if (TomatoLocked == true && Engine::GetGSComponent<DayByDay>()->getIsDraw() == false && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		texture[0].texturePtr->Draw(mat3<float>::build_translation(1220, 60));
	}
	if (IcecreamLocked == true && Engine::GetGSComponent<DayByDay>()->getIsDraw() == false && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		texture[0].texturePtr->Draw(mat3<float>::build_translation(1220, 491));
	}
}
