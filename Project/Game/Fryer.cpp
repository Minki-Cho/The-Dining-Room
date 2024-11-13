#include "Fryer.h"
#include "../Engine/Engine.h"
#include "Number.h"
#include "Unlock.h"
#include "DayByDay.h"
Fryer::Fryer(rect3 rect, Player* _player, FoodType _type)
	: WorkBench(rect, _player), type(_type)
{
	food = new Food(type);
	timer = 0;
	position = vec2(rect.point1.x - 6, rect.point1.y);
	gauge_position = vec2(rect.point1.x, rect.point2.y + 10);
	texture = Engine::GetTextureManager().Load("assets/images/map/fryer.png", false);
	gauge = Engine::GetTextureManager().Load("assets/images/gauge.png", false);
	bar = Engine::GetTextureManager().Load("assets/images/gauge_bar.png", false);
	numTex.Load("assets/images/numbers/2r.png");
}

void Fryer::Check()
{
	if (this->GetCheck() == true && player->GetIsOnTask() == true)
	{
		if (&player->GetFood() == nullptr)
		{
			isUpdate = true;
		}
	}
}

void Fryer::Update([[maybe_unused]] double dt)
{
	deltaTime = dt;
	if (Engine::GetGSComponent<DayByDay>()->GetDrawbool() == false)
	{
		if (isUpdate == true && this->GetCheck() == true)
		{
			isDraw = true;
			timer += static_cast<float>(dt);

			if (timer > 1.5)
			{
				isUpdate = false;
				isDraw = false;
				drawNumber = true;
				numPos = GetPosition();
				food->SetType(type);
				Engine::GetGSComponent<Number>()->UpdateNumber(-2);
				player->SetFood(*food);
				timer = 0;
			}
		}
	}
	else
	{
		timer = 0;
		isDraw = false;
		isUpdate = false;
	}

	if (drawNumber == true && drawTimer < 2.4)
	{
		drawTimer += dt;
	}
	else
	{
		drawNumber = false;
		drawTimer = true;
	}
}

void Fryer::Draw()
{
	texture->Draw(mat3<float>::build_translation(position));

	if (isDraw == true)
	{
		bar->Draw(mat3<float>::build_translation(gauge_position));
		gauge->Draw(mat3<float>::build_translation(gauge_position.x - 22 + timer * 15.5f, gauge_position.y) * mat3<float>::build_scale(timer * 0.7f, 1));
	}

	numPos.y += 20.f * static_cast<float>(deltaTime);
	mat3<float> mat = mat3<float>::build_translation(numPos) * mat3<float>::build_scale(0.5f);
	if (drawNumber == true)
		numTex.Draw(mat);
}
