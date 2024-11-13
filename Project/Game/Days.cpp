#include "Days.h"
#include "../Engine/Engine.h"

void Days::Add()
{
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/0.png",false),0 });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/1.png",false),1 });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/2.png",false),2 });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/3.png",false),3 });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/4.png",false),4 });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/5.png",false),5 });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/6.png",false),6 });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/7.png",false),7 });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/8.png",false),8 });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/9.png",false),9 });
}

void Days::Unload()
{
	texture.clear();
}

void Days::Update(double /*dt*/)
{
	if (Broke() == false)
	{

	}
}

void Days::Draw()
{
	unsigned int digits = 0;
	if (number >= 10)
	{
		if (number >= 100)
		{
			if (number >= 1000)
			{
				if (number >= 10000)
				{
					digits = static_cast<int>(number / 10000);
					texture[digits % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos.x - 160,startPos.y }));
				}
				digits = static_cast<int>(number / 1000);
				texture[digits % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos.x - 120,startPos.y }));
			}
			digits = static_cast<int>(number / 100);
			texture[digits % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos.x - 80,startPos.y }));
		}
		digits = static_cast<int>(number / 10);
		texture[digits % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos.x - 40,startPos.y }));
	}
	texture[number % 10].texturePtr->Draw(mat3<float>::build_translation(startPos));
}

void Days::UpdateNumber(int num)
{
	if (number >= 0)
	{
		number += num;
	}
}

void Days::SetNumber(int num)
{
	number = num;
}

int Days::GetNumber()
{
	return number;
}

bool Days::Broke()
{
	return (number <= 0);
}
