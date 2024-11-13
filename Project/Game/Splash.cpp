#include "Screens.h"
#include "Splash.h"
#include "../Engine/Engine.h"
#include "Sound_lists.h"

Splash::Splash() : modeNext(InputKey::Keyboard::Enter), timer(5)
{
	Engine::GetWindow().SetBackgroundColor(1,1,1,1);
}

Splash::~Splash()
{
}

void Splash::Load()
{
	//Sounds preload!
	SoundManager::sharedManager()->init();
	SoundManager::sharedManager()->loading("assets/sounds/The_Dining_Room_stage.wav",true,static_cast<int>(game_sounds::MAIN_MUSIC));
	SoundManager::sharedManager()->loading("assets/sounds/The_Dining_Room_main.wav", true, static_cast<int>(game_sounds::MENU_MUSIC));
	SoundManager::sharedManager()->loading("assets/sounds/The_Dining_Room_howto.wav", true, static_cast<int>(game_sounds::HOWTOPLAY));
	SoundManager::sharedManager()->loading("assets/sounds/clear_sound.wav", false, static_cast<int>(game_sounds::CLEAR_SOUND));
	SoundManager::sharedManager()->loading("assets/sounds/button_click.wav", false, static_cast<int>(game_sounds::CLICK_SOUND));
	SoundManager::sharedManager()->loading("assets/sounds/Store_taken_bgm.wav", true, static_cast<int>(game_sounds::STORETAKEN_ENDING));
	SoundManager::sharedManager()->loading("assets/sounds/Beep.wav", false, static_cast<int>(game_sounds::Beep));
	SoundManager::sharedManager()->loading("assets/sounds/Buy.wav", false, static_cast<int>(game_sounds::Buy));
	SoundManager::sharedManager()->loading("assets/sounds/Diary_Sound_Effect.wav", false, static_cast<int>(game_sounds::DIARY));
	SoundManager::sharedManager()->loading("assets/sounds/chash_sound.mp3", false, static_cast<int>(game_sounds::MONEY));
	SoundManager::sharedManager()->loading("assets/sounds/Times-out.wav", false, static_cast<int>(game_sounds::TIMEOUT));
	SoundManager::sharedManager()->loading("assets/sounds/Hit.wav", false, static_cast<int>(game_sounds::Hit));
	timer = 5;
	digipenLogo = Texture{ "assets/images/DigiPen_BLACK_1024px.png", false };
}

void Splash::Update(double dt)
{
	Engine::GetWindow().Clear();
	timer -= dt;
	if (modeNext.IsKeyReleased() == true || timer < 0 )
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
	}
}

void Splash::Draw()
{
	float x = 1280.f - digipenLogo.GetSize().x;
	float y = 720.f - digipenLogo.GetSize().y;
	digipenLogo.Draw(mat3<float>::build_translation({ x / 2, y / 2 }));
}

void Splash::Unload()
{
}