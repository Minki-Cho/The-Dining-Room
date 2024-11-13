#include "Screens.h"
#include "HowToPlay.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"
#include "Sound_lists.h"
#include "Direction.h"
#include "WorkBenchRange.h"
#include "Fryer.h"
#include "Counter.h"
#include "NormalWorkBench.h"
#include "TrashCan.h"
#include "Drinks.h"
#include "Kitchen.h"
#include "Wall.h"
#include "PickUpWorkBench.h"
#include "Unlock.h"
#include "Timer.h"
#include "Settings.h"


HowToPlay::HowToPlay()
{
	Engine::GetWindow().Clear();
}

void HowToPlay::Load()
{
	glCheck(glClearColor(1, 1, 1, 1));
	glCheck(glClear(GL_COLOR_BUFFER_BIT));
	SoundManager::sharedManager()->play(static_cast<int>(game_sounds::HOWTOPLAY), true);
	
	page = 0;
	count = 0;

	AddGSComponent(new Settings);

	BackGrounds.push_back(Texture("assets/images/howto/BackGrounds/BackGround.png", false));
	BackGrounds.push_back(Texture("assets/images/howto/BackGrounds/BackGround_pickup.png", false));

	ArrowKeys.Load("assets/images/howto/RightArrow.png");

	Bubbles.reserve(24);
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles1.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles2.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles3.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles4.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles5.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles6.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles7.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles8.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles9.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles10.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles11.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles12.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles13.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles14.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles15.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles16.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles17.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles18.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles19.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles20.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles21.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles22.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles23.png", false));
	Bubbles.push_back(Texture("assets/images/howto/Bubble/Bubbles24.png", false));

	Components.reserve(7);
	Components.push_back(Texture("assets/images/howto/components/checked_table.png", false));
	Components.push_back(Texture("assets/images/howto/components/customer.png", false));
	Components.push_back(Texture("assets/images/howto/components/customer_with_money.png", false));
	Components.push_back(Texture("assets/images/howto/components/rep.png", false));
	Components.push_back(Texture("assets/images/howto/components/dirty_table.png", false));
	Components.push_back(Texture("assets/images/howto/components/one.png", false));
	Components.push_back(Texture("assets/images/howto/components/two.png", false));


	gameObjectManager = new GameObjectManager();
	gameObjectManager->Add(new Wall({ vec3{ 0, 0, 1 }, vec3{ 170, 720, 1 } }));			//left
	gameObjectManager->Add(new Wall({ vec3{ 1270, 0, 1 }, vec3{ 1280, 720,1 } }));		//right
	gameObjectManager->Add(new Wall({ vec3{ 170, 0, 1 }, vec3{ 1270, 25, 1 } }));		//bottom
	gameObjectManager->Add(new Wall({ vec3{ 170, 585, 1 }, vec3{ 1270, 720, 1 } }));	//top

	//player
	playerPtr = new Player(vec2{ 1120, 240 });
	gameObjectManager->Add(playerPtr);

	//workbenches (size 48)
	//normal
	for (int i = 0; i < 7; i++)
	{
		if (i != 3 && i != 5)
		{
			workbenchPtr = new NormalWorkBench({ vec3{ 1220, 538 - (i * 48.f), 1}, vec3{1268, 588 - (i * 48.f), 1} }, playerPtr);
			gameObjectManager->Add(workbenchPtr);
			gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
		}
		else if (i == 3)	//drinks
		{
			workbenchPtr = new Drinks({ vec3{ 1220, 538 - (i * 48.f), 1}, vec3{1268, 588 - (i * 48.f), 1} }, playerPtr);
			gameObjectManager->Add(workbenchPtr);
			gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
		}
		else if (i == 5)	//fryer
		{
			workbenchPtr = new Fryer({ vec3{ 1220, 538 - (i * 48.f), 1}, vec3{1268, 588 - (i * 48.f), 1} }, playerPtr);
			gameObjectManager->Add(workbenchPtr);
			gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
		}
	}

	//TrashCan
	workbenchPtr = new TrashCan({ vec3{ 1220, 15, 1}, vec3{1268, 63, 1} }, playerPtr);
	gameObjectManager->Add(workbenchPtr);
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));

	for (int i = 0; i < 10; i++)
	{
		if (i != 3)
		{
			workbenchPtr = new NormalWorkBench({ vec3{ 982, 442 - (i * 48.f), 1}, vec3{1030, 492 - (i * 48.f), 1} }, playerPtr);
			gameObjectManager->Add(workbenchPtr);
			if (i == 0)
			{
				gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Top));
			}
			gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
			gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Right));
		}
		else if (i == 3)
		{
			//counter
			workbenchPtr = new Counter({ vec3{ 982, 442 - (i * 48.f), 1}, vec3{1030, 492 - (i * 48.f), 1} }, playerPtr);
			gameObjectManager->Add(workbenchPtr);
			gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Right));
		}
	}

	//ingredient
	for (int i = 1; i <= 4; i++)
	{
		workbenchPtr = new PickUpWorkBench({ vec3{ 1220, 250 - (i * 48.f), 1}, vec3{1268, 300 - (i * 48.f), 1} }, playerPtr, static_cast<FoodType>(i));
		gameObjectManager->Add(workbenchPtr);
		gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
	}

	AddGSComponent(gameObjectManager);

	//Table
	tablePtr = new Table({ vec3{744,105,1},vec3{794,205,1} }, playerPtr); // bottom right
	gameObjectManager->Add(tablePtr);
	tableList.push_back(reinterpret_cast<Table*>(workbenchPtr));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Right));

	highlight = new HighLight();
	highlight->Add();
	AddGSComponent(highlight);

	//vector of workbenches
	for (auto& g : gameObjectManager->Objects())
	{
		if (g->GetObjectType() == GameObjectType::WorkBenches)
		{
			workBenchList.push_back(static_cast<WorkBench*>(g));
		}
	}

	vol_number = new Volum_Number();
	vol_number->Add();
	AddGSComponent(vol_number);

	number = new Number();
	number->Add();
	AddGSComponent(number);

	AddGSComponent(new Unlock);

}

void HowToPlay::Update([[maybe_unused]] double dt)
{
	if (GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		switch (page)
		{
			//Move player
		case 4:
			playerPtr->Update(dt);
			gameObjectManager->CollideTest();
			if (playerPtr->GetIsOnTask() == true &&
				((playerPtr->GetPosition().x >= 654.992 && playerPtr->GetPosition().x <= 761.233
					&& playerPtr->GetPosition().y <= 217.417 && playerPtr->GetPosition().y >= 25)
					|| (playerPtr->GetPosition().x >= 654.992 + 100 && playerPtr->GetPosition().x <= 761.233 + 100
						&& playerPtr->GetPosition().y <= 217.417 && playerPtr->GetPosition().y >= 25)))
			{
				page++;
			}
			break;

			//pick up the patty
		case 7:
			playerPtr->Update(dt);
			gameObjectManager->CollideTest();
			GetGSComponent<Unlock>()->SetCheese(true);
			GetGSComponent<Unlock>()->SetLettuce(true);
			GetGSComponent<HighLight>()->Update(dt);

			if (playerPtr->GetIsOnTask() == true)
			{
				if (playerPtr->IsFoodOnHand() == true)
				{
					if (playerPtr->GetFood().GetType() == FoodType::PATTY)
					{
						page++;
					}
					else
					{
						page += 2;
					}
				}
			}
			break;

			//Make a burger
		case 11:
			gameObjectManager->Update(dt);
			if (playerPtr->IsFoodOnHand() == true)
			{
				if (playerPtr->GetFood().GetType() == FoodType::P)
				{
					page++;
				}
			}
			break;

			//give it to the guest
		case 13:
			gameObjectManager->Update(dt);
			if (playerPtr->GetFood().GetType() == FoodType::P)
			{
				if (playerPtr->GetIsOnTask() == true)
				{
					playerPtr->SetFoodToNull();
					page++;
				}
			}
			break;

			//Gather the money
		case 15:
			playerPtr->Update(dt);
			if (playerPtr->GetPosition().x >= 654.992 && playerPtr->GetPosition().x <= 761.233
				&& playerPtr->GetPosition().y <= 217.417 && playerPtr->GetPosition().y >= 25)
			{
				number->UpdateNumber(6);
				page++;
			}
			break;

			//clean the table
		case 19:
			playerPtr->Update(dt);

			if (playerPtr->GetPosition().x >= 654.992 && playerPtr->GetPosition().x <= 761.233
				&& playerPtr->GetPosition().y <= 217.417 && playerPtr->GetPosition().y >= 25)
			{
				if (playerPtr->GetIsOnTask() == true)
				{
					count++;
					if (count == 3)
					{
						page++;
					}
				}

			}
			break;

			//make the coke
		case 22:
			gameObjectManager->Update(dt);
			if (playerPtr->IsFoodOnHand() == true)
			{
				if (playerPtr->GetFood().GetType() == FoodType::COKE)
				{
					page++;
				}
			}
			break;

			//throw coke in the trash can
		case 24:
			gameObjectManager->Update(dt);
			if (playerPtr->IsFoodOnHand() == false)
			{
				playerPtr->SetFoodToNull();
				page++;
			}
			break;

			//make the frech fries
		case 26:
			playerPtr->SetFoodToNull();
			gameObjectManager->Update(dt);
			if (playerPtr->IsFoodOnHand() == true)
			{
				if (playerPtr->GetFood().GetType() == FoodType::FRENCHFRIES)
				{
					page++;
				}
			}
			break;

		//	//start of explanation of skill
		//case 27:
		//	if (modeNext.IsKeyReleased() == true)
		//	{
		//		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		//		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::ModeSelect));
		//	}
		//	if (backToMenu.IsKeyReleased() == true)
		//	{
		//		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		//		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
		//	}
		//	break;
		////buy dash in market
		//case 28:
		//	if (modeNext.IsKeyReleased() == true)
		//	{
		//		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		//		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::ModeSelect));
		//	}
		//	if (backToMenu.IsKeyReleased() == true)
		//	{
		//		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		//		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
		//	}
		//	break;

		////explantion of dash skill
		//case 29:
		//	if (modeNext.IsKeyReleased() == true)
		//	{
		//		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		//		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::ModeSelect));
		//	}
		//	if (backToMenu.IsKeyReleased() == true)
		//	{
		//		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		//		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
		//	}
		//	break;

		////using skill
		//case 30:
		//	if (modeNext.IsKeyReleased() == true)
		//	{
		//		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		//		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::ModeSelect));
		//	}
		//	if (backToMenu.IsKeyReleased() == true)
		//	{
		//		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		//		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
		//	}
		//	break;
		////defeat the thief
		//case 31:
		//	if (modeNext.IsKeyReleased() == true)
		//	{
		//		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		//		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::ModeSelect));
		//	}
		//	if (backToMenu.IsKeyReleased() == true)
		//	{
		//		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		//		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
		//	}
		//	break;

		//end of the tutorial
		case 32:
			if (modeNext.IsKeyReleased() == true)
			{
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::ModeSelect));
			}
			if (backToMenu.IsKeyReleased() == true)
			{
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
				Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
			}
			break;
		}

		//Mouse Pressed
		/*if (Engine::GetInput().GetFullScrean() == true)
		{
			if (page < 27 && (Engine::GetInput().GetMousePos().x > Engine::GetWindow().GetSize().x / 2.f + 558 / 2.f + 20.0f)
				&& (Engine::GetInput().GetMousePos().x < Engine::GetWindow().GetSize().x / 2.f + 558 / 2.f + 20.0f + 44)
				&& (Engine::GetInput().GetMousePos().y > Engine::GetWindow().GetSize().y / 2.f - 253 / 2.f + 110.0f)
				&& (Engine::GetInput().GetMousePos().y < Engine::GetWindow().GetSize().y / 2.f - 253 / 2.f + 110.0f + 51))
			{
				std::cout << "Here!\n" << std::endl;
				NextPagewithMouse();
			}
		}
		else
		{*/
			if (page < 32 && (Engine::GetInput().GetMousePos().x > 1280 / 2.f + 558 / 2.f + 20.0f)
				&& (Engine::GetInput().GetMousePos().x < 1280 / 2.f + 558 / 2.f + 20.0f + 44)
				&& (Engine::GetInput().GetMousePos().y > 720 / 2.f - 253 / 2.f + 110.0f)
				&& (Engine::GetInput().GetMousePos().y < 720 / 2.f - 253 / 2.f + 110.0f + 51))
			{
				std::cout << "Here\n" << std::endl;
				if (Engine::GetInput().GetMousePressed() == true && page < 27
					&& page != 4 && page != 7 && page != 11 && page != 13 && page != 15 && page != 19 && page != 22 && page != 24 && page != 26)
				{
					SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
					if (page == 8)
					{
						page = 10;
					}
					else
					{
						page++;
					}
				}
			}

		//}

		//KeyBoard
		if (NextPage.IsKeyReleased() == true
			&& page != 4 && page != 7 && page != 11 && page != 13 && page != 15 && page != 19 && page != 22 && page != 24 && page != 26)
		{
			SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
			if (page < 32)
			{
				if (page == 8)
				{
					page = 10;
				}
				else
				{
					page++;
				}
			}
		}

	}
	else if (Engine::GetInput().getPause() == true && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		GetGSComponent<Settings>()->Update(dt);
	}

	GetGSComponent<Settings>()->Update(dt);

}

void HowToPlay::Draw()
{
	BackGrounds[0].Draw(mat3<float>::build_translation({ 0.f,0.f }));

	std::cout << "page : " << page << std::endl;

	switch (page)
	{
	case 0:
		Bubbles[page].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[page].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[page].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[page].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[page].GetSize().y / 2.f + 90.0f }));
		break;

	case 1:
		Bubbles[page].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[page].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[page].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[page].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[page].GetSize().y / 2.f + 90.0f }));
		break;

	case 2:
		Bubbles[page].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[page].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[page].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[page].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[page].GetSize().y / 2.f + 90.0f }));
		playerPtr->Draw(mat3<float>::build_translation({ }));
		break;

	case 3:
		Bubbles[page].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[page].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[page].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[page].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[page].GetSize().y / 2.f + 90.0f }));
		playerPtr->Draw(mat3<float>::build_translation({ }));
		break;

	case 4:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Components[0].Draw(mat3<float>::build_translation(vec2(715.f, 48.f)) * mat3<float>::build_scale(vec2{ 0.46f }));
		GetGSComponent<HighLight>()->Draw();
		break;

	case 5:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[page - 1].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[page].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[page].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[page].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[page].GetSize().y / 2.f + 90.0f }));
		break;

	case 6:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[page - 1].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		break;

	case 7:
		BackGrounds[1].Draw(mat3<float>::build_translation({ 0.f,0.f }));
		playerPtr->Draw(mat3<float>::build_translation({ }));
		number->Draw();
		GetGSComponent<HighLight>()->Draw();
		break;

		//Patty ver.
	case 8:
		Bubbles[page - 2].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		playerPtr->Draw(mat3<float>::build_translation({ }));
		number->Draw();
		break;

		//else ver.
	case 9:
		Bubbles[page - 2].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		playerPtr->Draw(mat3<float>::build_translation({ }));
		number->Draw();
		break;

	case 10:
		Bubbles[page - 2].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		playerPtr->Draw(mat3<float>::build_translation({ }));
		number->Draw();
		break;

		//Make burger
	case 11:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Components[1].Draw(mat3<float>::build_translation({ (1280 / 2.f + Components[1].GetSize().height + 60.0f),  720 / 2.f - Components[1].GetSize().height / 2.f }));
		number->Draw();

		for (int i = 0; i < workBenchList.size(); i++)
		{
			if (i != 3 && i != 5 && i != 22)
			{
				workBenchList[i]->Draw();
			}
		}

		GetGSComponent<HighLight>()->Draw();
		break;

	case 12:
		Components[1].Draw(mat3<float>::build_translation({ (1280 / 2.f + Components[1].GetSize().height + 60.0f),  720 / 2.f - Components[1].GetSize().height / 2.f }));
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[page - 3].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		number->Draw();
		break;

		//give the burger to guest
	case 13:
		Components[1].Draw(mat3<float>::build_translation({ (1280 / 2.f + Components[1].GetSize().height + 60.0f),  720 / 2.f - Components[1].GetSize().height / 2.f }));
		playerPtr->Draw(mat3<float>::build_translation({ }));
		number->Draw();
		GetGSComponent<HighLight>()->Draw();
		break;

	case 14:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[page - 4].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		number->Draw();
		break;

		//gather money
	case 15:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		tablePtr->Draw();
		Components[2].Draw(mat3<float>::build_translation(vec2(680, 105)));
		number->Draw();
		break;

	case 16:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[page - 5].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(566, 600)));
		number->Draw();
		break;

	case 17:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[page - 5].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(566, 600)));
		number->Draw();
		break;

	case 18:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[page - 5].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(566, 600)));
		Components[4].Draw(mat3<float>::build_translation(vec2(707.f, 47.f)) * mat3<float>::build_scale(vec2{ 0.46f }));
		number->Draw();
		break;

	case 19:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Components[3].Draw(mat3<float>::build_translation(vec2(566, 600)));
		Components[4].Draw(mat3<float>::build_translation(vec2(707.f, 47.f)) * mat3<float>::build_scale(vec2{ 0.46f }));
		number->Draw();

		if (count == 1)
		{
			Components[5].Draw(mat3<float>::build_translation(vec2(745.f, 110.f)));
		}
		if (count == 2)
		{
			Components[6].Draw(mat3<float>::build_translation(vec2(745.f, 110.f)));
		}

		break;

	case 20:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[page - 6].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();

		break;

	case 21:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[page - 6].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();
		break;

		//make coke
	case 22:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		for (int i = 0; i < workBenchList.size(); i++)
		{
			//i = 5 -> fryer, 7 -> trashcan , 22 -> table
			if (i != 5 && i != 7 && i != 22)
			{
				workBenchList[i]->Draw();
			}
		}

		GetGSComponent<HighLight>()->Draw();
		number->Draw();

		break;

	case 23:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[page - 7].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();
		break;


		//trow coke in the trash can
	case 24:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();
		for (int i = 0; i < workBenchList.size(); i++)
		{
			//i = 3 -> drinks, 7 -> trashcan , 22 -> table
			if (i != 3 && i != 5 && i != 22)
			{
				workBenchList[i]->Draw();
			}
		}
		GetGSComponent<HighLight>()->Draw();
		break;

	case 25:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[17].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();
		break;

	case 26:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		for (int i = 0; i < workBenchList.size(); i++)
		{
			//i = 3 -> drinks, 7 -> trashcan , 22 -> table
			if (i != 3 && i != 7 && i != 22)
			{
				workBenchList[i]->Draw();
			}
		}

		GetGSComponent<HighLight>()->Draw();
		number->Draw();

		break;

	case 27:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[18].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();
		break;

	case 28:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[19].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));		
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();
		break;

	case 29:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[20].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();
		break;

	case 30:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[21].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();
		break;

	case 31:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[22].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		ArrowKeys.Draw(mat3<float>::build_translation({ (1280 / 2.f + Bubbles[0].GetSize().x / 2.f + 20.0f),  720 / 2.f - Bubbles[0].GetSize().y / 2.f + 90.0f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();
		break;

	case 32:
		playerPtr->Draw(mat3<float>::build_translation({ }));
		Bubbles[23].Draw(mat3<float>::build_translation({ 1280 / 2.f - Bubbles[0].GetSize().x / 2.f + 20.0f,  720 / 2.f - Bubbles[0].GetSize().y / 2.f }));
		Components[3].Draw(mat3<float>::build_translation(vec2(565, 601)));
		number->Draw();
		break;
	}

	GetGSComponent<Settings>()->Draw();

	if (GetGSComponent<Settings>()->GetOpenSettingScreen() == true)
	{
		GetGSComponent<Volum_Number>()->Draw();
	}
}

void HowToPlay::Unload()
{
	SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::HOWTOPLAY));
	gameObjectManager = nullptr;
	playerPtr = nullptr;
	workbenchPtr = nullptr;
	tablePtr = nullptr;
	number = nullptr;
	highlight = nullptr;
	BackGrounds.clear();
	Bubbles.clear();
	Components.clear();
	workBenchList.clear();
	ClearGSComponent();
}