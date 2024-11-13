#include "Screens.h"
#include "Diary.h"


#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"
#include <Random.h>

Diary::Diary() : timer(0), Isdraw(false),
Next(Button{ "assets/images/diary/button_play.png", "assets/images/cursor.png", {960, 261} })
{
	UpdateIndex();
	texture.push_back(new Texture("assets/images/diary/Diary1.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary2.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary3.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary4.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary5.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary6.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary7.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary8.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary9.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary10.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary11.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary12.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary13.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary14.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary15.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary16.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary17.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary18.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary19.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary20.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary21.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary22.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary23.png", false));
	texture.push_back(new Texture("assets/images/diary/Diary24.png", false));
	//texture.push_back(new Texture("assets/images/diary/Diary25.png", false));
	//texture.push_back(new Texture("assets/images/diary/Diary26.png", false));
	//texture.push_back(new Texture("assets/images/diary/Diary27.png", false));
	//texture.push_back(new Texture("assets/images/diary/Diary28.png", false));
	//texture.push_back(new Texture("assets/images/diary/Diary29.png", false));
	//texture.push_back(new Texture("assets/images/diary/Diary30.png", false));

	Next.SetIsHighlighted(false);
}

void Diary::Update(double /*dt*/)
{
	isNextClicked = false;

	if (Next.GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
		&& (Next.GetPosition().x + Next.GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
		&& Next.GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
		&& (Next.GetPosition().y + Next.GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
	{
		Next.SetIsHighlighted(true);
		if (Engine::GetInput().GetMousePressed() == true)
		{
			Engine::GetLogger().LogDebug("clicked");
			isNextClicked = true;
		}
	}
	else
		Next.SetIsHighlighted(false);

}

void Diary::Draw()
{
	if (Isdraw == true)
	{
		float x = 1280.f - texture[0]->GetSize().x;
		float y = 720.f - texture[0]->GetSize().y;
		texture[DiaryRandomized]->Draw(mat3<float>::build_translation({ x / 2, y / 2 }));
		Next.Draw();
	}
}

void Diary::Unload()
{
	texture.clear();
}

void Diary::SetDraw(bool type)
{
	Isdraw = type;
}

bool Diary::GetDrawbool()
{
	return Isdraw;
}

void Diary::UpdateIndex()
{
	DiaryRandomized = util::random(0, 23);
	//DiaryRandomized = util::random(0, 29);
}