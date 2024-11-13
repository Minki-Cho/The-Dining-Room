#include <stdexcept>	//std::exception
#include <iostream>		//std::cerr

#include "Engine/Engine.h"

#include "Game/Screens.h"
#include "Game/Splash.h"
#include "Game/MainMenu.h"
#include "Game/HowToPlay.h"
#include "Game/Credit.h"
#include "Game/ModeSelect.h"
#include "Game/StoryMode.h"
#include "Game/InfiniteMode.h"
#include "Game/GoodEnding.h"
#include "Game/NoGuestEnding.h"
#include "Game/StoreTakenEnding.h"
#include "Game/BadEnding.h"
#include "../Engine/fmod-sound.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv[])
{
	try
	{
		Engine& engine = Engine::Instance();
		engine.Init("The Dining Room");
		Splash splash;
		MainMenu mainmenu;
		HowToPlay howtoplay;
		Credit credit;
		ModeSelect modeselect;
		StoryMode sotrymode;
		InfiniteMode infinitemode;
		GoodEnding goodend;
		NoGuestEnding noguestend;
		StoreTakenEnding storetakenend;
		BadEnding badend;


		engine.GetGameStateManager().AddGameState(splash);
		engine.GetGameStateManager().AddGameState(mainmenu);
		engine.GetGameStateManager().AddGameState(howtoplay);
		engine.GetGameStateManager().AddGameState(credit);
		engine.GetGameStateManager().AddGameState(modeselect);
		engine.GetGameStateManager().AddGameState(sotrymode);
		engine.GetGameStateManager().AddGameState(infinitemode);
		engine.GetGameStateManager().AddGameState(goodend);
		engine.GetGameStateManager().AddGameState(noguestend);
		engine.GetGameStateManager().AddGameState(storetakenend);
		engine.GetGameStateManager().AddGameState(badend);
		while (engine.HasGameEnded() == false)
		{
			engine.Update();
			if (engine.GetInput().getIsdone() == true)
			{
				break;
			}
		}
		engine.Shutdown();
		SoundManager::sharedManager()->release();
		return 0;
	}
	catch (std::exception& e)
	{
		SoundManager::sharedManager()->release();
		std::cerr << e.what() << "\n";
		return -1;
	}
}