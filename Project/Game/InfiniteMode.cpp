#include "InfiniteMode.h"

#include <imgui.h>
#include <ImGuiHelper.h>

#include "mat3.h"
#include "Sound_lists.h"

#include "Wall.h"
#include "NormalWorkBench.h"
#include "PickUpWorkBench.h"
#include "Counter.h"
#include "WorkBenchRange.h"
#include "Drinks.h"
#include "Fryer.h"
#include "Icecream.h"

#include "Timer.h"
#include "Reputation.h"

#include "Screens.h"
#include "DayByDay.h"
#include "Result.h"
#include "Market.h"
#include "Ingredient.h"
#include "SideMenu.h"
#include "Skill.h"
#include "Diary.h"
#include "Settings.h"

#include "Pause.h"
#include "GameParticles.h"
#include "Unlock.h"
#include "Number.h"
#include "CleanUp.h"
#include "Double_Event.h"

#include "../Engine/Collision.h"
#include "../Engine/Engine.h"
#include "../Engine/Rect.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Input.h"
#include "../Engine/ComponentManager.h"
#include "../Engine/Window.h"

InfiniteMode::InfiniteMode() : guestTimer(0)
{
	Engine::GetWindow().Clear();
}

void InfiniteMode::Load()
{
	SoundManager::sharedManager()->play(static_cast<int>(game_sounds::MAIN_MUSIC), true);
	AddGSComponent(new Timer(GAMEPLAYTIME));
	AddGSComponent(new Reputation(50));
	AddGSComponent(new DayByDay);
	AddGSComponent(new Market);
	AddGSComponent(new ingredient);
	AddGSComponent(new SideMenu);
	AddGSComponent(new Skill);
	AddGSComponent(new Result(0, 0));
	AddGSComponent(new Pause);
	AddGSComponent(new Diary);
	AddGSComponent(new Settings);
	AddGSComponent(new CleanUp);
	gameScreen = new GameScreen();
	gameScreen->Add("assets/images/map/map.png");
	AddGSComponent(gameScreen);
	AddGSComponent(new Double_Event);

	gameObjectManager = new GameObjectManager();
	gameObjectManager->Add(new Wall({ vec3{ 0, 0, 1 }, vec3{ 170, 720, 1 } }));			//left
	gameObjectManager->Add(new Wall({ vec3{ 1270, 0, 1 }, vec3{ 1280, 720,1 } }));		//right
	gameObjectManager->Add(new Wall({ vec3{ 170, 0, 1 }, vec3{ 1270, 25, 1 } }));		//bottom
	gameObjectManager->Add(new Wall({ vec3{ 170, 585, 1 }, vec3{ 1270, 720, 1 } }));	//top

	//Food bubble
	foodbubble = new FoodBubble();
	foodbubble->Add("assets/images/bubble_long.png");
	AddGSComponent(foodbubble);

	//player
	playerPtr = new Player(vec2{ 1120, 240 });
	gameObjectManager->Add(playerPtr);

	//workbenches (size 48)
	//normal
	for (int i = 0; i < 6; i++)
	{
		if (i != 1 && i != 3 && i != 5)
		{
			workbenchPtr = new NormalWorkBench({ vec3{ 1220, 538 - (i * 48.f), 1}, vec3{1268, 588 - (i * 48.f), 1} }, playerPtr);
			gameObjectManager->Add(workbenchPtr);
			gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
		}
		else if (i == 1)	//icecream
		{
			workbenchPtr = new Icecream({ vec3{ 1220, 538 - (i * 48.f), 1}, vec3{1268, 588 - (i * 48.f), 1} }, playerPtr);
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
			counterPtr = new Counter({ vec3{ 982, 442 - (i * 48.f), 1}, vec3{1030, 492 - (i * 48.f), 1} }, playerPtr);
			workbenchPtr = counterPtr;
			gameObjectManager->Add(workbenchPtr);
			gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Right));
		}
	}

	vol_number = new Volum_Number();
	vol_number->Add();
	AddGSComponent(vol_number);

	//numbers
	number = new Number();
	number->Add();
	AddGSComponent(number);
	AddGSComponent(new Unlock);
	GetGSComponent<Unlock>()->Load("assets/images/lock.png");
	days = new Days();
	days->Add();
	AddGSComponent(days);

	//ingredient
	for (int i = 1; i <= 5; i++)
	{
		workbenchPtr = new PickUpWorkBench({ vec3{ 1220, 250 - ((i - 1) * 48.f), 1}, vec3{1268, 300 - ((i - 1) * 48.f), 1} }, playerPtr, static_cast<FoodType>(i));
		gameObjectManager->Add(workbenchPtr);
		gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
	}

	//table
	workbenchPtr = new Table({ vec3{458,105,1},vec3{508,205,1} }, playerPtr); // bottom left
	tableList.push_back(reinterpret_cast<Table*>(workbenchPtr));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Right));

	workbenchPtr = new Table({ vec3{458,395,1},vec3{508,495,1} }, playerPtr); // top left
	tableList.push_back(reinterpret_cast<Table*>(workbenchPtr));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Right));

	workbenchPtr = new Table({ vec3{602,395,1},vec3{652,495,1} }, playerPtr); // middle top
	tableList.push_back(reinterpret_cast<Table*>(workbenchPtr));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Right));

	workbenchPtr = new Table({ vec3{602,105,1},vec3{652,205,1} }, playerPtr); // middle bottom
	tableList.push_back(reinterpret_cast<Table*>(workbenchPtr));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Right));

	workbenchPtr = new Table({ vec3{744,105,1},vec3{794,205,1} }, playerPtr); // bottom right
	tableList.push_back(reinterpret_cast<Table*>(workbenchPtr));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Right));

	workbenchPtr = new Table({ vec3{744,395,1},vec3{794,495,1} }, playerPtr); // top right
	tableList.push_back(reinterpret_cast<Table*>(workbenchPtr));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Left));
	gameObjectManager->Add(new WorkBenchRange(workbenchPtr, Direction::Right));

	for (auto& t : tableList)
	{
		gameObjectManager->Add(t);
	}

	AddGSComponent(gameObjectManager);

	//Particles
	AddGSComponent(new MoneyEmitter());
	AddGSComponent(new SparkleEmitter());
	AddGSComponent(new DashEmitter());

	//background
	kitchen = new Kitchen();
	kitchen->Add("assets/images/map/map_interface.png");
	AddGSComponent(kitchen);

	GetGSComponent<Days>()->SetNumber(1);

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
	//money, 450,400
	money = new Money();
	money->Add("assets/images/coinbubble.png");
	AddGSComponent(money);

	//guestTimer
	guestTimer = 15;
	isTheif = false;
#ifdef _DEBUG
	AddGSComponent(new ShowCollision(InputKey::Keyboard::Q));
#endif() {}
}

void InfiniteMode::Update(double dt)
{
	GetGSComponent<GameObjectManager>()->Update(dt);
	if (Engine::GetInput().getPause() == false && GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		#ifdef _DEBUG
		if (cheat.IsKeyReleased() == true)
		{
			GetGSComponent<Timer>()->Cheat();
		}
		#endif
		if (GetGSComponent<Timer>()->HasEnded())
		{
			GetGSComponent<DayByDay>()->Update(dt);
			GetGSComponent<DayByDay>()->SetDraw(true);
			GetGSComponent<Result>()->Update(dt);
			GetGSComponent<Market>()->Update(dt);
			GetGSComponent<ingredient>()->Update(dt);
			GetGSComponent<SideMenu>()->Update(dt);
			GetGSComponent<Skill>()->Update(dt);
			GetGSComponent<Unlock>()->Update(dt);
			GetGSComponent<Diary>()->Update(dt);
			GetGSComponent<Result>()->SetDraw(true);
			GetGSComponent<Result>()->SetNum(GetGSComponent<Days>()->GetNumber(), GetGSComponent<Number>()->GetNumber());
			SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::MAIN_MUSIC));
			if (isPlaying == false)
			{
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLEAR_SOUND), false);
				isPlaying = true;
			}

			//clear.get()->Play();
		}
		GetGSComponent<Number>()->Update(dt);
		GetGSComponent<Timer>()->Update(dt);
		GetGSComponent<Reputation>()->Update(dt);

		//theif
		if (GetGSComponent<Days>()->GetNumber() % 10 == 0 && GetGSComponent<Timer>()->getTime() <= 35 && isTheif == false)
		{
			thiefPtr = new Thief({ 0,300 });
			gameObjectManager->Add(thiefPtr);
			isTheif = true;
		}

		//guest
		if (GetGSComponent<DayByDay>()->GetDrawbool() == false)
		{
			guestTimer -= dt;
			if (guestTimer < 0)
			{
				guestPtr = new Guest(tableList);
				guestPtr->SetCounter(counterPtr);
				gameObjectManager->Add(guestPtr);
				guestList.push_back(guestPtr);
				float rep = GetGSComponent<Reputation>()->getGauge();
				if (rep >= 0 && rep < 10)
				{
					guestTimer = 20;
				}
				else if (rep >= 10 && rep < 40)
				{
					guestTimer = 16;
				}
				else if (rep >= 40 && rep < 60)
				{
					guestTimer = 14;
				}
				else if (rep >= 60 && rep < 90)
				{
					guestTimer = 12;
				}
				else if (rep >= 90 && rep <= 100)
				{
					guestTimer = 10;
				}
			}
		}

		if (guestList.size() > 0)
		{
			if (guestList[0]->GetIsColideCounter() == true)
			{
				playerPtr->SetCanDelivery(true);
			}
		}

		if (GetGSComponent<DayByDay>()->GetDrawbool() == true)
		{
			thiefPtr = nullptr;
			guestList.clear();
			//Diary Screen
			if (next.IsKeyReleased() == true)
			{
				GetGSComponent<Diary>()->SetDraw(true);
			}

			if (GetGSComponent<Diary>()->GetDrawbool() == true)
			{
				GetGSComponent<DayByDay>()->SetMarketDraw(false);
				GetGSComponent<DayByDay>()->SetResultDraw(false);
				loadTimer += dt;
				if ((next.IsKeyReleased() == true || GetGSComponent<Diary>()->GetNextClicked() == true) && loadTimer > 0.5)
				{
					GetGSComponent<DayByDay>()->SetTomorrow(true);
					loadTimer = 0;
				}
			}

			//Diary Screen -> Next Day
			if (GetGSComponent<DayByDay>()->IsTomorrow() == true)
			{
				GetGSComponent<Diary>()->SetDraw(false); // <-if this is true, all day diary comes out
				GetGSComponent<Diary>()->UpdateIndex();
				GetGSComponent<DayByDay>()->SetTomorrow(false);
			}

			if (GetGSComponent<DayByDay>()->IsTomorrow() == false && GetGSComponent<Diary>()->GetDrawbool() == false && (next.IsKeyReleased() == true || GetGSComponent<Diary>()->GetNextClicked() == true))
			{
				GetGSComponent<DayByDay>()->SetDraw(false);
				GetGSComponent<Result>()->SetDraw(false);
				GetGSComponent<Market>()->SetDraw(false);
				GetGSComponent<ingredient>()->SetDraw(false);
				GetGSComponent<SideMenu>()->SetDraw(false);
				GetGSComponent<Skill>()->SetDraw(false);
				ClearMap();
				GetGSComponent<Days>()->UpdateNumber(1);
				SoundManager::sharedManager()->play(static_cast<int>(game_sounds::MAIN_MUSIC), true);
				guestTimer = 15;
				isPlaying = false;
				isTheif = false;
			}
		}
		if (GetGSComponent<Days>()->GetNumber() % 7 == 0 && GetGSComponent<DayByDay>()->GetDrawbool() == false)
		{
			// double gold event!
			GetGSComponent<Double_Event>()->SetIsEvent(true);
		}
		else
		{
			GetGSComponent<Double_Event>()->SetIsEvent(false);
		}
	}
	if (Engine::GetInput().getPause() == true && GetGSComponent<Settings>()->GetOpenSettingScreen() == false)
	{
		GetGSComponent<Pause>()->SetDraw(true);
	}
	else
	{
		GetGSComponent<Pause>()->SetDraw(false);
	}

	//Game Over
	if (GetGSComponent<Number>()->Broke() || GetGSComponent<Reputation>()->getGauge() == 0)
	{
		Engine::GetGameStateManager().SetNextState(static_cast<int>(Screens::Menu));
	}

	GetGSComponent<Settings>()->Update(dt);
#ifdef _DEBUG
	GetGSComponent<ShowCollision>()->Update(dt);
#endif {}
}

void InfiniteMode::ClearMap()
{
	playerPtr->SetToStartPosition();
	playerPtr->SetFoodToNull();
	playerPtr->SetCanDelivery(false);
	guestPtr = nullptr;
	thiefPtr = nullptr;
	guestList.clear();
	GetGSComponent<Timer>()->Reset(GAMEPLAYTIME);
	for (auto& g : GetGSComponent<GameObjectManager>()->Objects())
	{
		if (g->GetObjectTypeName() == "Normal WorkBench")
		{
			reinterpret_cast<NormalWorkBench*>(g)->SetEmpty();
		}
		if (g->GetObjectTypeName() == "Table")
		{
			reinterpret_cast<Table*>(g)->SetEmpty(true);
		}
	}
}

void InfiniteMode::Draw()
{
	GetGSComponent<GameScreen>()->Draw();
	GetGSComponent<Kitchen>()->Draw();
	GetGSComponent<Timer>()->Draw(vec2{ 1200, 650 });
	GetGSComponent<Reputation>()->DrawFace(vec2{ 570,620 });
	GetGSComponent<Reputation>()->DrawGauge(vec2{ 650,630 });
	for (auto& w : workBenchList)
	{
		w->Draw();
	}


	if (guestPtr != nullptr && guestPtr->drawMoney == true)
	{
		GetGSComponent<Money>()->Draw({ guestPtr->GameObject::GetPosition().x - 26, guestPtr->GameObject::GetPosition().y + 113 });
	}
	for (auto& o : gameObjectManager->Objects())
	{
		if (o->GetObjectType() == GameObjectType::Thief)
		{
			if (dynamic_cast<Thief*>(o)->steal_money == true)
			{
				GetGSComponent<Money>()->Draw({ dynamic_cast<Thief*>(o)->GetPosition().x - 26, dynamic_cast<Thief*>(o)->GetPosition().y + 113 });
			}
		}
	}
	GetGSComponent<Number>()->Draw();
	GetGSComponent<Days>()->Draw();
	GetGSComponent<HighLight>()->Draw();

	mat3<float> matrix = mat3<float>::build_scale(1);
	GetGSComponent<GameObjectManager>()->DrawAll(matrix);
	GetGSComponent<DayByDay>()->Draw();
	GetGSComponent<Pause>()->Draw();
	if (GetGSComponent<Double_Event>()->GetIsEvent() == true && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false
		&& Engine::GetInput().getPause() == false)
	{
		GetGSComponent<Double_Event>()->Draw();
	}
	GetGSComponent<Result>()->Draw();
	if (GetGSComponent<DayByDay>()->GetMarketDraw() == true)
	{
		GetGSComponent<Market>()->SetDraw(true);
		GetGSComponent<Market>()->Draw();

		GetGSComponent<ingredient>()->SetDraw(true);
		GetGSComponent<ingredient>()->Draw();

		GetGSComponent<SideMenu>()->SetDraw(true);
		GetGSComponent<SideMenu>()->Draw();

		GetGSComponent<Skill>()->SetDraw(true);
		GetGSComponent<Skill>()->Draw();
	}
	GetGSComponent<Settings>()->Draw();

	if (GetGSComponent<Diary>()->GetDrawbool() == true)
	{
		GetGSComponent<Diary>()->Draw();
	}
	if (GetGSComponent<Settings>()->GetOpenSettingScreen() == true && GetGSComponent<Diary>()->GetDrawbool() == false)
	{
		GetGSComponent<Volum_Number>()->Draw();
	}
	if (Engine::GetInput().getPause() == false && Engine::GetGSComponent<Settings>()->GetOpenSettingScreen() == false && Engine::GetGSComponent<Diary>()->GetDrawbool() == false)
	{
		GetGSComponent<Unlock>()->Draw();
	}
#ifdef _DEBUG
	ImGuiHelper::Begin();
	ImGui::Begin("Program Info");
	{
		ImGui::LabelText("WindowWidth", "%.1f", Engine::GetWindow().GetSize().x);
		ImGui::LabelText("WindowHeight", "%.1f", Engine::GetWindow().GetSize().y);
		ImGui::LabelText("Player-x", "%.1f", playerPtr->GetPosition().x);
		ImGui::LabelText("Player-y", "%.1f", playerPtr->GetPosition().y);
	}
	ImGui::End();
	ImGuiHelper::End(Engine::GetWindow().GetWindowPtr(), Engine::GetWindow().GetGLContext());
#endif 
}

void InfiniteMode::Unload()
{
	guestList.clear();
	SoundManager::sharedManager()->stop(static_cast<int>(game_sounds::MAIN_MUSIC));
	gameObjectManager = nullptr;
	kitchen = nullptr;
	foodbubble = nullptr;
	money = nullptr;
	playerPtr = nullptr;
	guestPtr = nullptr;
	thiefPtr = nullptr;
	workbenchPtr = nullptr;
	gameScreen = nullptr;
	vol_number = nullptr;
	orderList.clear();
	workBenchList.clear();
	tableList.clear();
	ClearGSComponent();
	isTheif = false;
}