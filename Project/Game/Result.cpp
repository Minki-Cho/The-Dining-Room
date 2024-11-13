#include "Result.h"
#include "../Engine/Engine.h"
#include "DayByDay.h"

#include <iostream>

Result::Result(long int day, long int money) : number1(day), number2(money), IsDraw(false)
{
	Add();

	//result with highligts
	buttons.push_back(new Button{ "assets/images/result/result_highlight.png", "assets/images/cursor.png", {135, 600} });

	//market without highligts
	buttons.push_back(new Button{ "assets/images/result/market.png", "assets/images/cursor.png", {303, 600} });
}

void Result::Add()
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

void Result::Unload()
{
	texture.clear();
	buttons.clear();
}

void Result::Update(double /*dt*/)
{
	//result Button
	if (buttons[0]->GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
		&& (buttons[0]->GetPosition().x + buttons[0]->GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
		&& buttons[0]->GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
		&& (buttons[0]->GetPosition().y + buttons[0]->GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
	{
		buttons[0]->SetIsHighlighted(true);

		if (Engine::GetInput().GetMousePressed() == true)
		{
			IsDraw = true;
			Engine::GetGSComponent<DayByDay>()->SetMarketDraw(false);
		}
	}
	else
	{
		buttons[0]->SetIsHighlighted(false);
	}

	//market Button
	if (buttons[1]->GetPosition().x * (Engine::GetWindow().GetSize().x / 1280.f) < Engine::GetInput().GetMousePos().x
		&& (buttons[1]->GetPosition().x + buttons[1]->GetSize().x) * (Engine::GetWindow().GetSize().x / 1280.f) > Engine::GetInput().GetMousePos().x
		&& buttons[1]->GetPosition().y * (Engine::GetWindow().GetSize().y / 720.f) < -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y)
		&& (buttons[1]->GetPosition().y + buttons[1]->GetSize().y) * (Engine::GetWindow().GetSize().y / 720.f) > -(Engine::GetInput().GetMousePos().y - Engine::GetWindow().GetSize().y))
	{
		buttons[1]->SetIsHighlighted(true);

		if (Engine::GetInput().GetMousePressed() == true)
		{
			Engine::GetLogger().LogDebug("clicked");
			IsDraw = false;
			Engine::GetGSComponent<DayByDay>()->SetMarketDraw(true);
			Engine::GetGSComponent<Market>()->SetDraw(true);

			std::cout << "market is : " << std::boolalpha << Engine::GetGSComponent<Market>()->GetIsDraw() << std::endl;
		}
	}
	else
	{
		buttons[1]->SetIsHighlighted(false);
	}
}

void Result::Draw()
{
	if (IsDraw == true && Engine::GetInput().getPause() == false)
	{
		buttons[0]->Draw();
		buttons[1]->Draw();

		unsigned int digits1 = 0;
		unsigned int digits2 = 0;
		if (number1 >= 10)
		{
			if (number1 >= 100)
			{
				if (number1 >= 1000)
				{
					if (number1 >= 10000)
					{
						digits1 = static_cast<int>(number1 / 10000);
						texture[digits1 % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos1.x - 160,startPos1.y }));
					}
					digits1 = static_cast<int>(number1 / 1000);
					texture[digits1 % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos1.x - 120,startPos1.y }));
				}
				digits1 = static_cast<int>(number1 / 100);
				texture[digits1 % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos1.x - 80,startPos1.y }));
			}
			digits1 = static_cast<int>(number1 / 10);
			texture[digits1 % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos1.x - 40,startPos1.y }));
		}
		texture[number1 % 10].texturePtr->Draw(mat3<float>::build_translation(startPos1));

		if (number2 >= 10)
		{
			if (number2 >= 100)
			{
				if (number2 >= 1000)
				{
					if (number2 >= 10000)
					{
						digits2 = static_cast<int>(number2 / 10000);
						texture[digits2 % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos2.x - 160,startPos2.y }));
					}
					digits2 = static_cast<int>(number2 / 1000);
					texture[digits2 % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos2.x - 120,startPos2.y }));
				}
				digits2 = static_cast<int>(number2 / 100);
				texture[digits2 % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos2.x - 80,startPos2.y }));
			}
			digits2 = static_cast<int>(number2 / 10);
			texture[digits2 % 10].texturePtr->Draw(mat3<float>::build_translation({ startPos2.x - 40,startPos2.y }));
		}
		texture[number2 % 10].texturePtr->Draw(mat3<float>::build_translation(startPos2));
		if (number2 < 10)
		{
			redTexture[number2].texturePtr->Draw(mat3<float>::build_translation(startPos2));
		}
	}
}

void Result::SetNum(long day, long money)
{
	number1 = day;
	number2 = money;
}

void Result::SetDraw(bool is_Draw)
{
	IsDraw = is_Draw;
}