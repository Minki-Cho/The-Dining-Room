#include "Pause.h"
#include "../Engine/Engine.h"

Pause::Pause() : Isdraw(false)
{
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/pause/1.png",false) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/pause/2.png",false) });
}
void Pause::Update(double /*dt*/)
{
}

void Pause::Draw()
{
	if (Isdraw == true)
	{
		float x = 1280.f - texture[0]->GetSize().x;
		float y = 720.f - texture[0]->GetSize().y;
		texture[0]->Draw(mat3<float>::build_translation({ x / 2, y / 2 }));
		texture[1]->Draw(mat3<float>::build_translation({ x / 2, -200 }));
	}
}

void Pause::Unload()
{
	texture.clear();
}

void Pause::SetDraw(bool type)
{
	Isdraw = type;
}

bool Pause::GetDrawbool()
{
	return Isdraw;
}
