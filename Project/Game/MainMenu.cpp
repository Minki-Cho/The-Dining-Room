#include <glCheck.h>

#include "Screens.h"
#include "MainMenu.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"
#include "Settings.h"
#include "VolumNumber.h"
#include "Loading.h"

MainMenu::MainMenu() :
	play(Button{ "assets/images/main/button_play.png", "assets/images/cursor.png", {Engine::GetWindow().GetSize().width * 0.75f, Engine::GetWindow().GetSize().height / 2.0f - 99} }),
	howtoplay(Button{ "assets/images/main/button_tutorial.png", "assets/images/cursor.png", {Engine::GetWindow().GetSize().width * 0.75f,  Engine::GetWindow().GetSize().height / 4.0f - 38} }),
	credit(Button{ "assets/images/main/button_credit.png", "assets/images/cursor.png", {Engine::GetWindow().GetSize().width * 0.75f, Engine::GetWindow().GetSize().height / 8.0f - 66} }),
	Enter(InputKey::Keyboard::Enter), Up(InputKey::Keyboard::Up), Down(InputKey::Keyboard::Down), Enter2(InputKey::Keyboard::Space), selectedIndex(0), check_is_music(false),
	background(Texture{ "assets/images/main/mainmenu.png", false})
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Load()
{
	AddGSComponent(new Loading);
	GetGSComponent<Loading>()->Add("assets/images/loading.png");
	SoundManager::sharedManager()->play(static_cast<int>(game_sounds::MENU_MUSIC), true);
	Engine::GetWindow().SetBackgroundColor(0.392f, 0.584f, 0.929f, 1);
	play.SetIsHighlighted(true);
	howtoplay.SetIsHighlighted(false);
	credit.SetIsHighlighted(false);
	selectedIndex = static_cast<int>(ButtonTypes::Play);

	AddGSComponent(new Settings);
	AddGSComponent(new Volum_Number);
	GetGSComponent<Volum_Number>()->Add();

	check_is_music = false;
}

void MainMenu::Update([[maybe_unused]] double dt)
{
	glCheck(glClear(GL_COLOR_BUFFER_BIT));
	if (check_is_music == false)
	{
		check_is_music = true;
	}

	GetGSComponent<Settings>()->Update(dt);

	if (GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		switch (selectedIndex)
		{
		case static_cast<int>(ButtonTypes::Play):
		{
			play.SetIsHighlighted(true);
			howtoplay.SetIsHighlighted(false);
			credit.SetIsHighlighted(false);
			break;
		}
		case static_cast<int>(ButtonTypes::HowToPlay):
		{
			play.SetIsHighlighted(false);
			howtoplay.SetIsHighlighted(true);
			credit.SetIsHighlighted(false);
			break;
		}
		case static_cast<int>(ButtonTypes::Credit):
		{
			play.SetIsHighlighted(false);
			howtoplay.SetIsHighlighted(false);
			credit.SetIsHighlighted(true);
			break;
		}
		}

		if (play.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (play.GetPosition().x + play.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& play.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (play.GetPosition().y + play.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			selectedIndex = static_cast<int>(ButtonTypes::Play);
			if (Engine::GetInput().GetMousePressed() == true)
			{
				isDrawLoading = true;
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
				SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::MENU_MUSIC));
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::ModeSelect));
			}
		}
		else if (howtoplay.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (howtoplay.GetPosition().x + howtoplay.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& howtoplay.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (howtoplay.GetPosition().y + howtoplay.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			selectedIndex = static_cast<int>(ButtonTypes::HowToPlay);
			if (Engine::GetInput().GetMousePressed() == true)
			{
				isDrawLoading = true;
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Howtoplay));
			}
		}
		else if (credit.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
			&& (credit.GetPosition().x + credit.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
			&& credit.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
			&& (credit.GetPosition().y + credit.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
		{
			selectedIndex = static_cast<int>(ButtonTypes::Credit);
			if (Engine::GetInput().GetMousePressed() == true)
			{
				isDrawLoading = true;
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Credit));
			}
		}

		if (Down.IsKeyReleased() == true)
		{
			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
			switch (selectedIndex)
			{
			case static_cast<int>(ButtonTypes::Play):
				selectedIndex = static_cast<int>(ButtonTypes::HowToPlay);
				break;

			case static_cast<int>(ButtonTypes::HowToPlay):
				selectedIndex = static_cast<int>(ButtonTypes::Credit);
				break;

			case static_cast<int>(ButtonTypes::Credit):
				break;
			default:
				break;
			}
		}

		if (Up.IsKeyReleased() == true)
		{
			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
			switch (selectedIndex)
			{
			case static_cast<int>(ButtonTypes::Play):
				break;

			case static_cast<int>(ButtonTypes::HowToPlay):
				selectedIndex = static_cast<int>(ButtonTypes::Play);
				break;

			case static_cast<int>(ButtonTypes::Credit):
				selectedIndex = static_cast<int>(ButtonTypes::HowToPlay);
				break;
			default:
				break;
			}
		}

		if (Engine::GetInput().getPause() == false)
		{
			if (Enter.IsKeyReleased() == true || Enter2.IsKeyReleased() == true)
			{
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
				switch (selectedIndex)
				{
				case static_cast<int>(ButtonTypes::Play):
					isDrawLoading = true;
					SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::MENU_MUSIC));
					Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::ModeSelect));
					break;

				case static_cast<int>(ButtonTypes::HowToPlay):
					isDrawLoading = true;
					Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Howtoplay));
					break;

				case static_cast<int>(ButtonTypes::Credit):
					isDrawLoading = true;
					Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Credit));
					break;
				default:
					break;
				}
			}
		}
	}
}

void MainMenu::Draw()
{
	
	background.Draw(mat3<float>::build_translation(vec2{0,0}));
	play.Draw();
	howtoplay.Draw();
	credit.Draw();
	GetGSComponent<Settings>()->Draw();
	if (GetGSComponent<Settings>()->GetOpenSettingScreen() == true)
	{
		GetGSComponent<Volum_Number>()->Draw();
	}
	if (isDrawLoading == true)
	{
		GetGSComponent<Loading>()->Draw();
	}
}

void MainMenu::Unload()
{
	isDrawLoading = false;
	SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::MENU_MUSIC));
	ClearGSComponent();
}
