#include "Screens.h"
#include "StoreTakenEnding.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"
#include "Sound_lists.h"

StoreTakenEnding::StoreTakenEnding()
	: modeNext(InputKey::Keyboard::Enter), backToMenu(InputKey::Keyboard::Space), EndingScreen("assets/images/endings/storeTaken.png", false), isMusic(false)
{
}

void StoreTakenEnding::Load()
{
	glCheck(glClearColor(1, 1, 1, 1));
	glCheck(glClear(GL_COLOR_BUFFER_BIT));
	SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLEAR_SOUND), false);
	
}

void StoreTakenEnding::Update(double/* dt*/)
{
	if (isMusic == false)
	{
		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::STORETAKEN_ENDING), true);
		isMusic = true;
	}
	Draw();
	if (modeNext.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::StoryMode));
	}
	if (backToMenu.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
	}
}

void StoreTakenEnding::Draw()
{
	float x = 1280.f - EndingScreen.GetSize().x;
	float y = 720.f - EndingScreen.GetSize().y;
	EndingScreen.Draw(mat3<float>::build_translation({ x / 2, y / 2 }));
}

void StoreTakenEnding::Unload()
{
	SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::STORETAKEN_ENDING));
}