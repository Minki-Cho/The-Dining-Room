#include "Thief.h"
#include "../Engine/Engine.h"

#include "DayByDay.h"
#include "Theif_Anims.h"

#include "../Engine/fmod-sound.h"
#include "Sound_lists.h"
#include "Reputation.h"
#include "../Engine/Rect.h"
#include "../Engine/Collision.h"
#include "Number.h"

Thief::Thief(vec2 _startPos) : startPos(_startPos), GameObject(_startPos)
{
	AddGOComponent(new Sprite("assets/images/characters/thief/thief.spt", this));
	texturePtr = Engine::GetTextureManager().Load("assets/images/thief.png", false);
	currState = &staterunning_right;
	currState->Enter(this);
}

Thief::~Thief()
{
}

void Thief::Update(double dt)
{
	timer += dt;
	GameObject::Update(dt);
	GameObject::UpdatePosition(GetVelocity());

	if (Engine::GetGSComponent<DayByDay>()->GetDrawbool() == true)
	{
		SetDestroyed(true);
	}
}

bool Thief::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Player)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Thief::ResolveCollision(GameObject* objectB)
{
	rect3 guestRect = GetGOComponent<RectCollision>()->GetWorldCoorRect();
	rect3 collideRect = objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect();

	if (objectB->GetObjectType() == GameObjectType::Player && steal_money == true)
	{
		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::Hit), false);
		SetDestroyed(true);
		ClearGOComponents();
		Engine::GetGSComponent<Reputation>()->Increase(4);
	}
}

void Thief::Draw(mat3<float> displayMatrix)
{
	if (static_cast<int>(timer) % 2 == 0)
	{
		texturePtr->Draw(mat3<float>::build_translation(30, 120));
	}
	
	GameObject::Draw(displayMatrix);
}

void Thief::StateRunning_Right::Enter(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	thief->animNumber = 7;
	thief->GetGOComponent<Sprite>()->PlayAnimation(thief->animNumber);
}

void Thief::StateRunning_Right::Update(GameObject* object, double dt)
{
	Thief* thief = static_cast<Thief*>(object);
	if (thief->GetPosition().x < limit)
	{
		thief->SetVelocity(vec2{ static_cast<float>(speed * dt), 0 });
	}
	else
	{
		moving_one_end = true;
	}
}

void Thief::StateRunning_Right::TestForExit(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	if (moving_one_end == true)
	{
		thief->ChangeState(&thief->staterunning_up);
	}
}

void Thief::StateRunning_Up::Enter(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	thief->animNumber = 5;
	thief->GetGOComponent<Sprite>()->PlayAnimation(thief->animNumber);
}

void Thief::StateRunning_Up::Update(GameObject* object, double dt)
{
	Thief* thief = static_cast<Thief*>(object);
	if (thief->GetPosition().y < limit)
	{
		thief->SetVelocity(vec2{ 0, static_cast<float>(speed * dt) });
	}
	else
	{
		moving_two_end = true;
	}
}

void Thief::StateRunning_Up::TestForExit(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	if (moving_two_end == true)
	{
		thief->ChangeState(&thief->staterunning_right2);
	}
}

void Thief::StateRunning_Right2::Enter(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	thief->animNumber = 7;
	thief->GetGOComponent<Sprite>()->PlayAnimation(thief->animNumber);
}

void Thief::StateRunning_Right2::Update(GameObject* object, double dt)
{
	Thief* thief = static_cast<Thief*>(object);
	if (moving_two_end == false && thief->GetPosition().x < 1050)
	{
		thief->SetVelocity(vec2{ static_cast<float>(speed * dt), 0 });
	}
	else
	{
		moving_two_end = true;
	}
}

void Thief::StateRunning_Right2::TestForExit(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	if (moving_two_end == true)
	{
		thief->ChangeState(&thief->staterunning_down);
	}
}

void Thief::StateRunning_Down::Enter(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	thief->animNumber = 4;
	thief->GetGOComponent<Sprite>()->PlayAnimation(thief->animNumber);
}

void Thief::StateRunning_Down::Update(GameObject* object, double dt)
{
	Thief* thief = static_cast<Thief*>(object);
	if (thief->GetPosition().y > 300)
	{
		thief->SetVelocity(vec2{ 0, -static_cast<float>(speed * dt) });
	}
	else
	{
		timer += dt;
		thief->animNumber = 2;
		thief->GetGOComponent<Sprite>()->PlayAnimation(thief->animNumber);
		thief->SetVelocity(vec2{ 0, 0 });
	}
	if (timer > 2)
	{
		moving_two_end = true;
	}
}

void Thief::StateRunning_Down::TestForExit(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	if (moving_two_end == true)
	{
		thief->ChangeState(&thief->statesteal);
	}
}

void Thief::StateSteal::Enter(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	thief->animNumber = 5;
	thief->GetGOComponent<Sprite>()->PlayAnimation(thief->animNumber);
}

void Thief::StateSteal::Update(GameObject* object, double dt)
{
	Thief* thief = static_cast<Thief*>(object);
	if (thief->GetPosition().y < limit)
	{
		thief->SetVelocity(vec2{ 0, static_cast<float>(speed * dt) });
	}
	else
	{
		thief->steal_money = true;
		moving_two_end = true;
	}
}

void Thief::StateSteal::TestForExit(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	if (moving_two_end == true)
	{
		thief->ChangeState(&thief->statesteal_left);
	}
}

void Thief::StateSteal_Left::Enter(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	thief->animNumber = 6;
	thief->GetGOComponent<Sprite>()->PlayAnimation(thief->animNumber);
}

void Thief::StateSteal_Left::Update(GameObject* object, double dt)
{
	Thief* thief = static_cast<Thief*>(object);
	if (thief->GetPosition().x > 200)
	{
		thief->SetVelocity(vec2{ -static_cast<float>(speed * 1.7 * dt), 0 });
	}
	else
	{
		moving_two_end = true;
	}
}

void Thief::StateSteal_Left::TestForExit(GameObject* object)
{
	Thief* thief = static_cast<Thief*>(object);
	if (moving_two_end)
	{
		Engine::GetGSComponent<Reputation>()->Decrease(4);
		Engine::GetGSComponent<Number>()->UpdateNumber(-2);
		thief->SetDestroyed(true);
		thief->ClearGOComponents();
	}
}
