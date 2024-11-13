#pragma once
#include <glCheck.h>

#include "../Engine/GameState.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"

class BadEnding : public GameState
{
public:
	BadEnding();
	void Load() override;
	void Draw() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() override { return "BadEnding"; }

private:
	Texture EndingScreen;
	InputKey modeNext;
	InputKey backToMenu;
};