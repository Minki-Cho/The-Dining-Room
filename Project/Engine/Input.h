#pragma once
#include <SDL2/SDL.h>
#include <vector> //vector array
#include "vec2.h"
#undef main

class InputKey
{
public:
	enum class Keyboard
	{
		None, Enter, Escape, Space, BackSpace, Shift, Left, Up, Right, Down,
		A, B, C, D, E, F, G, H, I, J,
		K, L, M, N, O, P, Q, R, S, T,
		U, V, W, X, Y, Z,
		Count
	};

	InputKey(Keyboard button);
	bool IsKeyDown() const;
	bool IsKeyReleased() const;
private:
	Keyboard button;
};

class Input
{
public:
	Input();
	bool IsKeyDown(InputKey::Keyboard key) const;
	bool IsKeyReleased(InputKey::Keyboard key) const;
	void SetKeyDown(InputKey::Keyboard key, bool value);
	void Update();
	bool getIsdone() { return isDone;  }
	bool getPause() { return pause;  }
	void setPause(bool b) { pause = b; };
	vec2 GetMousePos() { return mousePos; }
	bool GetMousePressed() { return isMousePressed;  }
	void toggleFullScreen() { fullScreen = !fullScreen; };
	bool GetFullScrean() { return fullScreen; }
private:
	std::vector<bool> isKeyDownList;
	std::vector<bool> wasKeyDownList;
	bool isDone = false;
	bool pause = false;
	vec2 mousePos = {0,0};
	bool isMouseDown{ false };
	bool isMouseUp{ false };
	bool isMousePressed{ false };
	bool fullScreen{ false };
};
inline SDL_Event event;