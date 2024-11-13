#pragma once
#include <glCheck.h>

#include "../Engine/GameState.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"

class NoGuestEnding : public GameState
{
public:
	NoGuestEnding();
	void Load() override;
	void Draw() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() override { return "NoGuestEnding"; }

private:
	Texture EndingScreen;
	InputKey modeNext;
	InputKey backToMenu;
};