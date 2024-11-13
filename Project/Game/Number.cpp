#include "Number.h"
#include "Settings.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"

Number::Number() : cheat(InputKey::Keyboard::M)
{
	/*vol_num = SoundManager::sharedManager()->getCurrentVolume();*/
}

void Number::Add()
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

	redTexture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/0r.png",false),0 });
	redTexture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/1r.png",false),1 });
	redTexture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/2r.png",false),2 });
	redTexture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/3r.png",false),3 });
	redTexture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/4r.png",false),4 });
	redTexture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/5r.png",false),5 });
	redTexture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/6r.png",false),6 });
	redTexture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/7r.png",false),7 });
	redTexture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/8r.png",false),8 });
	redTexture.push_back({ Engine::GetTextureManager().Load("assets/images/numbers/9r.png",false),9 });
}

void Number::Unload()
{
	texture.clear();
	redTexture.clear();
}

void Number::Update(double /*dt*/)
{
	if (Broke() == false)
	{

	}
#ifdef _DEBUG
	if (cheat.IsKeyReleased() == true)
	{
		number += 10;
	}
#endif
}

void Number::Draw()
{
	if (Engine::GetInput().getPause() == false)
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
		if (number < 10 && number > 0)
		{
			redTexture[number].texturePtr->Draw(mat3<float>::build_translation(startPos));
		}
	}
}

void Number::UpdateNumber(int num)
{
	if (number > 0)
	{
		number += num;
	}
}

void Number::SetNumber(int num)
{
	number = num;
}

int Number::GetNumber()
{
	return number;
}

bool Number::Broke()
{
	return (number <= 0);
}
