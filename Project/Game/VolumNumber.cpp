#include "VolumNumber.h"
#include "Settings.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"

Volum_Number::Volum_Number()
{
	number = SoundManager::sharedManager()->getCurrentVolume();
}

void Volum_Number::Add()
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

void Volum_Number::Unload()
{
	texture.clear();
}

void Volum_Number::Update(double /*dt*/)
{
	number = SoundManager::sharedManager()->getCurrentVolume();
}

void Volum_Number::Draw()
{
	unsigned int digits = 0;
	if (number >= 10)
	{
		if (number >= 100)
		{
			digits = static_cast<int>(number / 100);
			texture[digits % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos.x - 80,startPos.y }));
		}
		digits = static_cast<int>(number / 10);
		texture[digits % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos.x - 40,startPos.y }));
	}
	texture[number % 10].texturePtr->Draw(mat3<float>::build_translation(startPos));

}

void Volum_Number::UpdateNumber(int num)
{
	if (number > 0)
	{
		number += num;
	}
}

void Volum_Number::SetNumber(int num)
{
	number = num;
}

int Volum_Number::GetNumber()
{
	return number;
}

bool Volum_Number::Broke()
{
	return (number <= 0);
}
