#pragma once
#include "../Engine/GameState.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/Button.h"

class ModeSelect : public GameState
{
public:
	enum class ButtonTypes
	{
		Story,
		Infinite,
		MainMenu,
	};

	ModeSelect();
	~ModeSelect();
	void Load() override;
	void Draw() override;
	void Update(double dt) override;
	void Unload() override;
	std::string GetName() override { return "ModeSelect"; }

private:
	int selectedIndex;

	Texture background;
	Texture loading;
	Button story, infinite, mainmenu;

	InputKey Enter;
	InputKey Enter2;
	InputKey left;
	InputKey right;
	bool check_is_music;
	bool isLoading;
	bool IsLoading_image;
};