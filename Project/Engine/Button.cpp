#include "Button.h"

Button::Button(const std::filesystem::path& _button, const std::filesystem::path& _cursor, vec2 _pos) : position(_pos)
{
	button = Texture{ _button, false };
	cursor = Texture{ _cursor, false };
}

void Button::Draw()
{
	button.Draw((mat3<float>::build_translation(position)));
	
	if (isHighlighted == true)
	{
		cursor.Draw((mat3<float>::build_translation(position + button.GetSize() * 0.75f)));
	}
}

void Button::Update()
{
}

void Button::SetIsHighlighted(bool _status)
{
	isHighlighted = _status;
}
