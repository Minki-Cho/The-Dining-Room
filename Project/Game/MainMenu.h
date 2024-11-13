#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/Button.h"

class MainMenu : public GameState
{
public:
	enum class ButtonTypes
	{
		Play,
		HowToPlay,
		Credit,
	};

	MainMenu();
	~MainMenu();
	void Load() override;
	void Draw() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() override { return "MainMenu"; }

private:
	int selectedIndex;
	
	Texture background;
	Button play, howtoplay, credit;

	InputKey Enter;
	InputKey Enter2;
	InputKey Up;
	InputKey Down;
	bool check_is_music;
	bool isDrawLoading = false;
};