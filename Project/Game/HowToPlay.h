#pragma once
#include <glCheck.h>

#include "../Engine/GameState.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "GameScreen.h"
#include "../Engine/GameObjectManager.h"
#include "WorkBench.h"
#include "Table.h"
#include "HighLight.h"
#include "Number.h"
#include "Player.h"
#include "VolumNumber.h"

class HowToPlay : public GameState
{
public:
    HowToPlay();
    void Load() override;
    void Draw() override;
    void Update(double dt) override;
    void Unload() override;
    std::string GetName() override { return "HowToPlay"; }

private:
    int page;
    int count;

    Texture ArrowKeys;

    std::vector<Texture> BackGrounds;
    std::vector<Texture> Bubbles;
    std::vector<Texture> Components;

    InputKey NextPage = InputKey::Keyboard::Enter;
    InputKey modeNext = InputKey::Keyboard::Enter;
    InputKey backToMenu = InputKey::Keyboard::BackSpace;

    std::vector<Table*> tableList;

    Player* playerPtr{ nullptr };
    std::vector<WorkBench*> workBenchList = {};
    Table* tablePtr{ nullptr };
    HighLight* highlight{ nullptr };
    GameObjectManager* gameObjectManager{ nullptr };
    WorkBench* workbenchPtr{ nullptr };
    Number* number{ nullptr };
    Volum_Number* vol_number{ nullptr };

    void NextPagewithMouse();
};