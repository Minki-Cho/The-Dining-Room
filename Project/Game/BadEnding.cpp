#include "Screens.h"
#include "BadEnding.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"
#include "Sound_lists.h"

BadEnding::BadEnding()
	: modeNext(InputKey::Keyboard::Enter), backToMenu(InputKey::Keyboard::Space), EndingScreen("assets/images/endings/bad.png", false)
{
}

void BadEnding::Load()
{
	glCheck(glClearColor(1, 1, 1, 1));
	glCheck(glClear(GL_COLOR_BUFFER_BIT));
	SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLEAR_SOUND), false);
}

void BadEnding::Update(double/* dt*/)
{
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

void BadEnding::Draw()
{
	float x = 1280.f - EndingScreen.GetSize().x;
	float y = 720.f - EndingScreen.GetSize().y;
	EndingScreen.Draw(mat3<float>::build_translation({ x / 2, y / 2 }));
}

void BadEnding::Unload()
{
}