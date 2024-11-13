#pragma once
#include <glCheck.h>

#include "../Engine/GameState.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"

class Credit : public GameState
{
public:
	Credit();
	void Load() override;
	void Draw() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() override { return "Credit"; }

private:
	Texture background;
	Texture credit;

	vec2 creditPosition;

	InputKey backToMain;
	InputKey backToMain2;
};