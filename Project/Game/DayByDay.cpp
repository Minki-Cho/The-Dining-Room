#include "Screens.h"
#include "DayByDay.h"
#include "Unlock.h"

#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"

DayByDay::DayByDay() : timer(0), Isdraw(false), texture(new Texture("assets/images/daybyday.png", false)), result_draw(true), market_draw(false) {}

void DayByDay::Update(double /*dt*/) {}

void DayByDay::Draw()
{
	if (Isdraw == true)
	{
		float x = 1280.f - texture->GetSize().x;
		float y = 720.f - texture->GetSize().y;
		texture->Draw(mat3<float>::build_translation({ x / 2, y / 2 }));
	}
}

void DayByDay::Unload()
{
	delete texture;
}

void DayByDay::SetDraw(bool type)
{
	Isdraw = type;
}

bool DayByDay::GetDrawbool()
{
	if (this != nullptr)
	{
		return Isdraw;
	}
	else
	{
		return false;
	}
}