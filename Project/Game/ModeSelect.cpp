#include <glCheck.h>

#include "Screens.h"
#include "ModeSelect.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"
//#include "Settings.h"
//#include "VolumNumber.h"
#include "Loading.h"

ModeSelect::ModeSelect() :
	story(Button{ "assets/images/select_page/storymode.png", "assets/images/cursor.png", {36.f, 720.f - 543.f} }),
	infinite(Button{ "assets/images/select_page/infinitemode.png", "assets/images/cursor.png", {442.f,720.f - 543.f} }),
	mainmenu(Button{ "assets/images/select_page/mainmenu.png", "assets/images/cursor.png", {846.f,720.f - 543.f} }),
	Enter(InputKey::Keyboard::Enter), left(InputKey::Keyboard::Left), right(InputKey::Keyboard::Right), Enter2(InputKey::Keyboard::Space), selectedIndex(0), check_is_music(false),
	background(Texture{ "assets/images/select_page/select_mode_background.png", false }), loading(Texture{ "assets/images/loading.png", false }), isLoading(false), IsLoading_image(false)
{
}

ModeSelect::~ModeSelect()
{
}

void ModeSelect::Load()
{
	SoundManager::sharedManager()->play(static_cast<int>(game_sounds::MENU_MUSIC), true);
	Engine::GetWindow().SetBackgroundColor(0.392f, 0.584f, 0.929f, 1);
	story.SetIsHighlighted(true);
	infinite.SetIsHighlighted(false);
	mainmenu.SetIsHighlighted(false);
	selectedIndex = static_cast<int>(ButtonTypes::Story);

	//AddGSComponent(new Settings);
	//AddGSComponent(new Volum_Number);
	//GetGSComponent<Volum_Number>()->Add();

	check_is_music = false;
	isLoading = false;

	AddGSComponent(new Loading);
	GetGSComponent<Loading>()->Add("assets/images/loading.png");
}

void ModeSelect::Update([[maybe_unused]] double dt)
{
	glCheck(glClear(GL_COLOR_BUFFER_BIT));
	if (check_is_music == false)
	{
		check_is_music = true;
	}

	//GetGSComponent<Settings>()->Update(dt);

	//if (GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		switch (selectedIndex)
		{
		case static_cast<int>(ButtonTypes::Story):
		{
			story.SetIsHighlighted(true);
			infinite.SetIsHighlighted(false);
			mainmenu.SetIsHighlighted(false);
			break;
		}
		case static_cast<int>(ButtonTypes::Infinite):
		{
			story.SetIsHighlighted(false);
			infinite.SetIsHighlighted(true);
			mainmenu.SetIsHighlighted(false);
			break;
		}
		case static_cast<int>(ButtonTypes::MainMenu):
		{
			story.SetIsHighlighted(false);
			infinite.SetIsHighlighted(false);
			mainmenu.SetIsHighlighted(true);
			break;
		}
		}

		if (story.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (story.GetPosition().x + story.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& story.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (story.GetPosition().y + story.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			selectedIndex = static_cast<int>(ButtonTypes::Story);
			if (Engine::GetInput().GetMousePressed() == true)
			{
				isLoading = true;
				Draw();
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
				SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::MENU_MUSIC));
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::StoryMode));
			}
		}
		else if (infinite.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (infinite.GetPosition().x + infinite.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& infinite.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (infinite.GetPosition().y + infinite.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			selectedIndex = static_cast<int>(ButtonTypes::Infinite);
			if (Engine::GetInput().GetMousePressed() == true)
			{
				isLoading = true;
				Draw();
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::InfiniteMode));
			}
		}
		else if (mainmenu.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (mainmenu.GetPosition().x + mainmenu.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& mainmenu.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (mainmenu.GetPosition().y + mainmenu.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			selectedIndex = static_cast<int>(ButtonTypes::MainMenu);
			if (Engine::GetInput().GetMousePressed() == true)
			{
				isLoading = true;
				Draw();
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
			}

		}
		

		if (left.IsKeyReleased() == true)
		{
			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);


			switch (selectedIndex)
			{
			case static_cast<int>(ButtonTypes::Story):
				break;

			case static_cast<int>(ButtonTypes::Infinite):
				selectedIndex = static_cast<int>(ButtonTypes::Story);
				break;

			case static_cast<int>(ButtonTypes::MainMenu):
				selectedIndex = static_cast<int>(ButtonTypes::Infinite);
				break;
			default:
				break;
			}
		}

		if (right.IsKeyReleased() == true)
		{
			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
			switch (selectedIndex)
			{
			case static_cast<int>(ButtonTypes::Story):
				selectedIndex = static_cast<int>(ButtonTypes::Infinite);
				break;

			case static_cast<int>(ButtonTypes::Infinite):
				selectedIndex = static_cast<int>(ButtonTypes::MainMenu);
				break;

			case static_cast<int>(ButtonTypes::MainMenu):
				break;
			default:
				break;
			}
		}

		if (Enter.IsKeyReleased() == true || Enter2.IsKeyReleased() == true)
		{

			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
			switch (selectedIndex)
			{
			case static_cast<int>(ButtonTypes::Story):
				isLoading = true;
				Draw();
				SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::MENU_MUSIC));
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::StoryMode));
				break;

			case static_cast<int>(ButtonTypes::Infinite):
				isLoading = true;
				Draw();
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::InfiniteMode));
				break;

			case static_cast<int>(ButtonTypes::MainMenu):
				isLoading = true;
				Draw();
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
				break;
			default:
				break;
			}
		}

	}

}

void ModeSelect::Draw()
{
	if (isLoading == false)
	{
		background.Draw(mat3<float>::build_translation(vec2{ 0,0 }));
		story.Draw();
		infinite.Draw();
		mainmenu.Draw();
		//GetGSComponent<Settings>()->Draw();
		//if (GetGSComponent<Settings>()->GetOpenSettingScreen() == true)
		/*{
			GetGSComponent<Volum_Number>()->Draw();
		}*/
	}
	else if (isLoading == true)
	{
		GetGSComponent<Loading>()->Draw();
		//loading.Draw(mat3<float>::build_translation(vec2{ 0,0 }));
		IsLoading_image = true;
		
	}
}

void ModeSelect::Unload()
{
	SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::MENU_MUSIC));
	ClearGSComponent();
}
