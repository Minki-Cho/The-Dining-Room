#pragma once
#include "Texture.h"

class Button
{
public:
	Button() = default;
	Button(const std::filesystem::path& _button, const std::filesystem::path& _cursor, vec2 _pos);
	void Draw();
	void Update();
	void SetIsHighlighted(bool _status);
	bool GetIsHighlighted() { return isHighlighted; };
	vec2 GetPosition() { return position; }
	vec2 GetSize() { return button.GetSize(); };
private:
	vec2 position;

	bool isSelected;
	bool isHighlighted;

	Texture button;
	Texture cursor;
};