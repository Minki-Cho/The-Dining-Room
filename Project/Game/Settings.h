#pragma once
#include <glCheck.h>
#include <array>

#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/Button.h"
#include "../Engine/Component.h"

class Settings : public Component
{
public:
	enum class ButtonTypes
	{
		FullScreen,
		MainMenu,
		Exit,
	};

	Settings();
	void Update(double dt) override;
	void Draw();
	bool GetOpenSettingScreen() { return openSettingScreen; }
private:
	Button settingButton;
	Texture settingScreen;

	InputKey Up, Down, Left, Right;
	InputKey Esc;
	InputKey Enter, Enter2;

	int selectedIndex;
	bool openSettingScreen{ false };
	bool sound{ false };
	std::array<Button, 7> buttons;
};