#include "Screens.h"
#include "Credit.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"
#include "Sound_lists.h"

Credit::Credit() : backToMain(InputKey::Keyboard::Enter), backToMain2(InputKey::Keyboard::Space),
background("assets/images/credit/background.png", false), credit("assets/images/credit/credit.png", false)
{
}

void Credit::Load()
{
	SoundManager::sharedManager()->play(static_cast<int>(game_sounds::MENU_MUSIC), true);
	glCheck(glClearColor(1, 1, 1, 1));
	glCheck(glClear(GL_COLOR_BUFFER_BIT));
	creditPosition = { 0, -credit.GetSize().y };
}

void Credit::Update(double/* dt */)
{
	if (creditPosition.y < background.GetSize().height/2.f - 100)
	{
		creditPosition.y += 1.5f;
	}

	Draw();

	if (backToMain.IsKeyReleased() == true || backToMain2.IsKeyReleased() == true)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
	}
}

void Credit::Draw()
{
	background.Draw(mat3<float>::build_translation({ 0,0 }));
	credit.Draw(mat3<float>::build_translation(0, creditPosition.y));
}

void Credit::Unload()
{
	SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::MENU_MUSIC));
}