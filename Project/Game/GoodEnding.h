#pragma once
#include <glCheck.h>

#include "../Engine/GameState.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"

class GoodEnding : public GameState
{
public:
	GoodEnding();
	void Load() override;
	void Draw() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() override { return "GoodEnding"; }

private:
	Texture EndingScreen;
	InputKey modeNext;
};