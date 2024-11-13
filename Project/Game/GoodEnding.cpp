#include "Screens.h"
#include "GoodEnding.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"
#include "Sound_lists.h"

GoodEnding::GoodEnding()
	: modeNext(InputKey::Keyboard::Enter), EndingScreen("assets/images/endings/good.png", false)
{
}

void GoodEnding::Load()
{
	glCheck(glClearColor(1, 1, 1, 1));
	glCheck(glClear(GL_COLOR_BUFFER_BIT));
	SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLEAR_SOUND), false);
}

void GoodEnding::Update(double/* dt*/)
{
	Draw();
	if (modeNext.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Credit));
	}
}

void GoodEnding::Draw()
{
	float x = 1280.f - EndingScreen.GetSize().x;
	float y = 720.f - EndingScreen.GetSize().y;
	EndingScreen.Draw(mat3<float>::build_translation({ x / 2, y / 2 }));
}

void GoodEnding::Unload()
{
}