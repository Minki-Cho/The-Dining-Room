#include "Screens.h"
#include "Settings.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"
#include "VolumNumber.h"

Settings::Settings() : Esc(InputKey::Keyboard::Escape), Up(InputKey::Keyboard::Up), Down(InputKey::Keyboard::Down),
Left(InputKey::Keyboard::Left), Right(InputKey::Keyboard::Right), Enter(InputKey::Keyboard::Enter), Enter2(InputKey::Keyboard::Space)
{
	openSettingScreen = false;
	selectedIndex = static_cast<int>(ButtonTypes::FullScreen);
	buttons[3].SetIsHighlighted(true);
	buttons[5].SetIsHighlighted(false);
	buttons[6].SetIsHighlighted(false);
	settingButton = Button("assets/images/pause-button.png", "assets/images/cursor.png", vec2{ 0.f,0.f });
	settingScreen = Texture("assets/images/settings/background.png", false);
	//backButton
	buttons[0] = Button("assets/images/settings/back.png", "assets/images/cursor.png", vec2{ 1092.f,552.f });
	//volumeUp
	buttons[1] = Button("assets/images/settings/up.png", "assets/images/cursor.png", vec2{ 580.f,399.f });
	//volumeDown
	buttons[2] = Button("assets/images/settings/down.png", "assets/images/cursor.png", vec2{ 976.f,399.f });
	//fullScreen
	buttons[3] = Button("assets/images/settings/fullScreen.png", "assets/images/cursor.png", vec2{ 67.f,140.f });
	//windowmod
	buttons[4] = Button("assets/images/settings/windowmod.png", "assets/images/cursor.png", vec2{ 67.f,140.f });
	//mainMenu
	buttons[5] = Button("assets/images/settings/mainmenu.png", "assets/images/cursor.png", vec2{ 441.f,140.f });
	//exit
	buttons[6] = Button("assets/images/settings/exit.png", "assets/images/cursor.png", vec2{ 815.f,140.f });
}

void Settings::Update(double dt )
{
	Engine::GetGSComponent<Volum_Number>()->Update(dt);

	if (openSettingScreen)
		Engine::GetInput().setPause(true);

	//open settingScreen by pressing Esc
	if (Esc.IsKeyReleased() == true)
	{
		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
		openSettingScreen = !openSettingScreen;
	}

	//Click settingButton
	if (settingButton.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
		&& (settingButton.GetPosition().x + settingButton.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
		&& settingButton.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
		&& (settingButton.GetPosition().y + settingButton.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
	{
		settingButton.SetIsHighlighted(true);
		if (openSettingScreen == false && Engine::GetInput().GetMousePressed() == true)
		{
			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
			openSettingScreen = true;
			//Engine::GetInput().setPause(true);
		}
	}
	else
		settingButton.SetIsHighlighted(false);

	if (openSettingScreen == true)
	{
		//Keyboard Input
		if (Up.IsKeyReleased())
		{
			//volumeUp
			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
			SoundManager::sharedManager()->volumeUp();
		}
		if (Down.IsKeyReleased())
		{
			//volumeDown
			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
			SoundManager::sharedManager()->volumeDown();
		}

		if (Left.IsKeyReleased() == true)
		{
			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
			switch (selectedIndex)
			{
			case static_cast<int>(ButtonTypes::FullScreen):
				break;
			case static_cast<int>(ButtonTypes::MainMenu):
				selectedIndex = static_cast<int>(ButtonTypes::FullScreen);
				break;
			case static_cast<int>(ButtonTypes::Exit):
				selectedIndex = static_cast<int>(ButtonTypes::MainMenu);
				break;
			default:
				break;
			}
		}

		if (Right.IsKeyReleased() == true)
		{
			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
			switch (selectedIndex)
			{
			case static_cast<int>(ButtonTypes::FullScreen):
				selectedIndex = static_cast<int>(ButtonTypes::MainMenu);
				break;
			case static_cast<int>(ButtonTypes::MainMenu):
				selectedIndex = static_cast<int>(ButtonTypes::Exit);
				break;
			case static_cast<int>(ButtonTypes::Exit):
				break;
			default:
				break;
			}
		}

		switch (selectedIndex)
		{
		case static_cast<int>(ButtonTypes::FullScreen):
		{
			//FullScreen
			if (Engine::GetInput().GetFullScrean() == false)
				buttons[3].SetIsHighlighted(true);
			else
				buttons[4].SetIsHighlighted(true);
			//MainMenu
			buttons[5].SetIsHighlighted(false);
			//Exit
			buttons[6].SetIsHighlighted(false);
			break;
		}
		case static_cast<int>(ButtonTypes::MainMenu):
		{
			//FullScreen
			if (Engine::GetInput().GetFullScrean() == false)
				buttons[3].SetIsHighlighted(false);
			else
				buttons[4].SetIsHighlighted(false);
			//MainMenu
			buttons[5].SetIsHighlighted(true);
			//Exit
			buttons[6].SetIsHighlighted(false);
			break;
		}
		case static_cast<int>(ButtonTypes::Exit):
		{
			//FullScreen
			if (Engine::GetInput().GetFullScrean() == false)
				buttons[3].SetIsHighlighted(false);
			else
				buttons[4].SetIsHighlighted(false);
			//MainMenu
			buttons[5].SetIsHighlighted(false);
			//Exit
			buttons[6].SetIsHighlighted(true);
			break;
		}
		}

		if (Enter.IsKeyReleased() == true || Enter2.IsKeyReleased() == true)
		{
			switch (selectedIndex)
			{
			case static_cast<int>(ButtonTypes::FullScreen):
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
				Engine::GetInput().toggleFullScreen();
				break;
			case static_cast<int>(ButtonTypes::MainMenu):
				if (Engine::GetGameStateManager().GetName() == "MainMenu")
				{
					SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Beep), false);
					break;
				}
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
				openSettingScreen = false;
				Engine::GetInput().setPause(false);
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
				break;
			case static_cast<int>(ButtonTypes::Exit):
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
				Engine::GetGameStateManager().Shutdown();
				break;
			default:
				break;
			}
		}
	}

	//settingScreen
	for (int b = 0; b < buttons.size(); ++b)
	{
		if (openSettingScreen == true)
		{
			if (buttons[b].GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
				&& (buttons[b].GetPosition().x + buttons[b].GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
				&& buttons[b].GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
				&& (buttons[b].GetPosition().y + buttons[b].GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
			{
				buttons[b].SetIsHighlighted(true);
				switch (b)
				{
				case 3:
				case 4:
					selectedIndex = static_cast<int>(ButtonTypes::FullScreen);
					break;
				case 5:
					selectedIndex = static_cast<int>(ButtonTypes::MainMenu);
					break;
				case 6:
					selectedIndex = static_cast<int>(ButtonTypes::Exit);
				}

				if (Engine::GetInput().GetMousePressed() == true)
				{
					switch (b)
					{
					case 0:
						//backButton
						SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
						openSettingScreen = false;
						Engine::GetInput().setPause(false);
						break;
					case 1:
						//volumeUp
						SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
						SoundManager::sharedManager()->volumeUp();
						std::cout << SoundManager::sharedManager()->getCurrentVolume() << std::endl;
						break;
					case 2:
						//volumeDown
						SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
						SoundManager::sharedManager()->volumeDown();
						std::cout << SoundManager::sharedManager()->getCurrentVolume() << std::endl;
						break;
					case 3:	//fullScreen
						break;
					case 4:	//windowmod
						SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
						Engine::GetInput().toggleFullScreen();
						break;
					case 5:
						//mainMenu
						if (Engine::GetGameStateManager().GetName() == "MainMenu")
						{
							SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Beep), false);
							break;
						}
						SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
						openSettingScreen = false;
						Engine::GetInput().setPause(false);
						Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
						break;
					case 6:
						//exit
						SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), true);
						Engine::GetGameStateManager().Shutdown();
						break;
					}
				}
			}
			else if (b >= 0 && b < 3)
				buttons[b].SetIsHighlighted(false);
		}
	}
}

void Settings::Draw()
{
	settingButton.Draw();
	if (openSettingScreen == true)
	{
		settingScreen.Draw(mat3<float>::build_translation(vec2{ 0.f,0.f }));

		for (int i = 0; i < static_cast<int>(buttons.size()); i++)
		{
			if (Engine::GetInput().GetFullScrean() == true)
			{
				if (i != 3)
				{
					buttons[i].Draw();
				}
			}
			else
			{
				if (i != 4)
				{
					buttons[i].Draw();
				}
			}
		}
	}
}