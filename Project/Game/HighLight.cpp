#include "HighLight.h"
#include "../Engine/Engine.h"
void HighLight::Add()
{
	texture = Engine::GetTextureManager().Load("assets/images/yellow.png", false);
}

void HighLight::Unload()
{
	Engine::GetTextureManager().Unload();
}

void HighLight::SetPos(vec2 position)
{
	Pos = position;
}

void HighLight::Draw()
{
	if( IsDraw == true )
	{
		texture->Draw(mat3<float>::build_translation(Pos));
	}
}

vec2 HighLight::Size()
{
	return texture->GetSize();
}

void HighLight::SetIsDrawing(bool check)
{
	IsDraw = check;
}

bool HighLight::GetIsDraw()
{
	return IsDraw;
}
