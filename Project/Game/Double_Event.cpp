#include "Double_Event.h"

Double_Event::Double_Event() :Event_texture("assets/images/Money_double.png", false)
{
}

void Double_Event::Update(double /*dt*/)
{
}

void Double_Event::Draw()
{
	if (isEvent == true)
	{
		Event_texture.Draw(mat3<float>::build_translation(startPos));
	}
}

void Double_Event::Unload()
{
}
