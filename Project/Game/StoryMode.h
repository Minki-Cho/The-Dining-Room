#pragma once
#include <array>

#include "Kitchen.h"
#include "Player.h"
#include "GameScreen.h"
#include "Guest.h"
#include "FoodBubble.h"
#include "Money.h"
#include "WorkBench.h"
#include "Table.h"
#include "TrashCan.h"
#include "Number.h"
#include "HighLight.h"
#include "Days.h"
#include "VolumNumber.h"
#include "Thief.h"

#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Input.h"
#include "../Engine/fmod-sound.h"

class StoryMode : public GameState
{
public:
	StoryMode();
	void Load() override;
	void Draw() override;
	void Update(double dt) override;
	void Unload() override;
	void ClearMap();
	std::string GetName() override { return "StoryMode"; }
private:
	InputKey next = InputKey::Keyboard::Enter;
	InputKey cheat = InputKey::Keyboard::T;

	GameObjectManager* gameObjectManager{ nullptr };
	Kitchen* kitchen{ nullptr };
	FoodBubble* foodbubble{ nullptr };
	Money* money{ nullptr };
	Number* number{ nullptr };
	Volum_Number* vol_number{ nullptr };
	Days* days{ nullptr };
	HighLight* highlight{ nullptr };
	Player* playerPtr{ nullptr };
	Guest* guestPtr{ nullptr };
	WorkBench* workbenchPtr{ nullptr };
	GameScreen* gameScreen{ nullptr };
	Thief* thiefPtr{ nullptr };
	Counter* counterPtr{ nullptr };

	std::vector<WorkBench*> workBenchList = {};
	std::vector<Table*> tableList = {};
	std::vector<Guest*> guestList = {};

	double guestTimer;
	bool isPlaying = false;
	static constexpr int GAMEPLAYTIME{ 120 };
	double loadTimer{ 0 };
	bool isTheif = false;
};