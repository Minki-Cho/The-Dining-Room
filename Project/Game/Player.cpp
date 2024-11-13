#include <iostream>

#include "Player.h"
#include "WorkBenchRange.h"

#include "../Engine/Sprite.h"
#include "../Engine/Collision.h"
#include "../Engine/ShowCollision.h"
#include "../Engine/Rect.h"
#include "../Engine/GameStateManager.h"
#include "../Engine/Engine.h"
#include "../Engine/fmod-sound.h"
#include "Sound_lists.h"
#include "GameParticles.h"
#include "Unlock.h"
#include "Timer2.h"
#include "angles.h"

Player::Player(vec2 _startPos) : Up(InputKey::Keyboard::Up), Down(InputKey::Keyboard::Down),
Left(InputKey::Keyboard::Left), Right(InputKey::Keyboard::Right), Space(InputKey::Keyboard::Space), Shift(InputKey::Keyboard::Shift),
startPos(_startPos), GameObject(_startPos), isOnTask(false), food(nullptr)
{
	speed = 5.5f;

	AddGOComponent(new Sprite("assets/images/player/player_2.spt", this));
	currState = &stateIdle;
	currState->Enter(this);
	direction = CharacterAnim::None_F;
	AddGOComponent(new Timer2(6)); // set cooldown duration to 4 seconds
}

Player::~Player()
{
}

void Player::Update(double dt)
{
	GameObject::Update(dt);
	GameObject::UpdatePosition(GetVelocity());

	//hardcoded for the unexpected bug for the player.
	if (GetPosition().x < 170 || GetPosition().x > 1270 || GetPosition().y < 0 || GetPosition().y > 585)
	{
		SetPosition(startPos);
	}
	
	//Keyboard Released
	if (Space.IsKeyReleased() == true)
	{
		SoundManager::sharedManager()->play(static_cast<int>(game_sounds::CLICK_SOUND), false);
		isOnTask = true;
	}
	else
	{
		isOnTask = false;
	}
	//}

	//skill update
	if (Engine::GetGSComponent<Unlock>()->GetUnlockDash() == true)
	{
		// Dash started
		if (UsingDash == false && Shift.IsKeyReleased() && CooltimeActive == false)
		{
			speed *= 1.7f;
			UsingDash = true;
			CooltimeActive = true;
			GetGOComponent<Timer2>()->Reset(1); // set dash duration to 1 seconds
			Engine::GetGameStateManager().GetGSComponent<DashEmitter>()->Emit(7, GetPosition() + vec2{ 0,GetGOComponent<Sprite>()->GetFrameSize().y / 2 }, vec2{ 0,1.f }, vec2{ 100.f,0.f }, util::HALF_PI<float>);
		}

		// During dash
		if (UsingDash == true)
		{
			GetGOComponent<Timer2>()->Update(dt);

			// Dash finished
			if (GetGOComponent<Timer2>()->getTime() <= 0.f)
			{
				UsingDash = false;
				speed = 5.5f;
				GetGOComponent<Timer2>()->Reset(6); // set cooldown duration to 4 seconds
			}
		}

		// During cooldown
		else if (CooltimeActive == true)
		{
			GetGOComponent<Timer2>()->Update(dt);

			// Cooldown finished
			if (GetGOComponent<Timer2>()->getTime() <= 0.f)
			{
				CooltimeActive = false;
			}
		}
	}
}

void Player::Draw(mat3<float> TransformMatrix)
{
	GetGOComponent<Timer2>()->Draw({ 100, 300 });
	if (food != nullptr)
	{
		if ((direction == CharacterAnim::Front) || (direction == CharacterAnim::None_F)
			|| (direction == CharacterAnim::H_Front) || (direction == CharacterAnim::H_None_F))	//front
		{
			GameObject::Draw(TransformMatrix);
			food->Draw(TransformMatrix * mat3<float>::build_translation(GetPosition() + vec2{ 0, 30 }));
		}
		else if ((direction == CharacterAnim::Left) || (direction == CharacterAnim::None_L)
			|| (direction == CharacterAnim::H_Left) || (direction == CharacterAnim::H_None_L))	//front
		{
			food->Draw(TransformMatrix * mat3<float>::build_translation(GetPosition() + vec2{ -10, 30 }));
			GameObject::Draw(TransformMatrix);
		}
		else if ((direction == CharacterAnim::Right) || (direction == CharacterAnim::None_R)
			|| (direction == CharacterAnim::H_Right) || (direction == CharacterAnim::H_None_R))	//front
		{
			food->Draw(TransformMatrix * mat3<float>::build_translation(GetPosition() + vec2{ 10, 30 }));
			GameObject::Draw(TransformMatrix);
		}
		else  //back
		{
			food->Draw(TransformMatrix * mat3<float>::build_translation(GetPosition() + vec2{ 0, 30 }));
			GameObject::Draw(TransformMatrix);
		}
	}
	else
	{
		GameObject::Draw(TransformMatrix);
	}
}

const vec2& Player::GetPosition() const
{
	return GameObject::GetPosition();
}

bool Player::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Wall || objectBType == GameObjectType::WorkBenches)
	{
		return true;
	}
	return false;
}

void Player::ResolveCollision(GameObject* objectB)
{
	rect3 collideRect = objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect();
	rect3 playerRect = GetGOComponent<RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType())
	{
	case GameObjectType::Wall:
	case GameObjectType::WorkBenches:
		if (GameObject::GetVelocity().y < 0)
		{
			if (playerRect.Bottom() < collideRect.Top() && playerRect.Top() > collideRect.Top())	// Down
			{
				UpdatePosition(vec2{ 0.0,collideRect.Top() - playerRect.Bottom() });
				SetVelocity({ 0, 0 });
			}
		}
		if (GameObject::GetVelocity().y > 0)
		{
			if (playerRect.Top() > collideRect.Bottom() && playerRect.Bottom() < collideRect.Bottom())	// Up
			{
				UpdatePosition(vec2{ 0.0,-(playerRect.Top() - collideRect.Bottom()) });
				SetVelocity({ 0, 0 });
			}
		}
		if (GameObject::GetVelocity().x > 0)
		{
			if (playerRect.Right() > collideRect.Left() && playerRect.Right() < collideRect.Right()) // Right
			{
				UpdatePosition(vec2{ collideRect.Left() - playerRect.Right() - 2,0.0 });
				SetVelocity({ 0, 0 });
			}
		}
		if (GameObject::GetVelocity().x < 0)
		{
			if (playerRect.Left() < collideRect.Right() && playerRect.Left() > collideRect.Left()) // Left
			{
				UpdatePosition(vec2{ collideRect.Right() - playerRect.Left() + 2,0.0 });
				SetVelocity({ 0, 0 });
			}
		}
		if (objectB->GetObjectTypeName() == "Fryer" || objectB->GetObjectTypeName() == "Drinks")
		{
			reinterpret_cast<WorkBench*>(objectB)->SetCheckTrue();
		}
		else
			reinterpret_cast<WorkBench*>(objectB)->SetCheckFalse();
		break;
	default:
		break;
	}
}

bool& Player::GetIsOnTask()
{
	return isOnTask;
}

Food& Player::GetFood()
{
	return *(this->food);
}

bool Player::IsFoodOnHand()
{
	return (food != nullptr);
}

void Player::SetToStartPosition()
{
	this->SetPosition(startPos);
	timer = 0;
	GetGOComponent<Timer2>()->Reset(0);
	CooltimeActive = false;
	UsingDash = false;
	speed = 5.5;
}

void Player::SetFood(Food& _food)
{
	this->food = &_food;
}

void Player::SetFoodToNull()
{
	food = nullptr;
}

void Player::SetIsSuccess()
{
	isSuccess = !isSuccess;
}

bool& Player::GetIsSuccess()
{
	return isSuccess;
}

void Player::SetLastOrder(FoodType _type)
{
	lastOrder = _type;
}

void Player::SetCanDelivery(bool b)
{
	canDelivery = b;
}

FoodType& Player::GetLastOrder()
{
	return lastOrder;
}

bool Player::GetCanDelivery()
{
	return canDelivery;
}

bool Player::GetCanMove()
{
	return canMove;
}

//--------------------------------------------------------

//StateIdle
void Player::StateIdle::Enter([[maybe_unused]] GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->SetVelocity(vec2{ 0, 0 });
	player->GetGOComponent<Sprite>()->PlayAnimation(static_cast<int>(player->direction));
	Engine::GetLogger().LogEvent("IDLE");
}

void Player::StateIdle::Update([[maybe_unused]] GameObject* object, [[maybe_unused]] double dt)
{
}

void Player::StateIdle::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);

	bool A_down = player->Left.IsKeyDown();
	bool D_down = player->Right.IsKeyDown();
	bool W_down = player->Up.IsKeyDown();
	bool S_down = player->Down.IsKeyDown();

	//if (player->GetCanMove() == true)
	//{
	if (A_down)
	{
		player->direction = CharacterAnim::Left;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Left;
		player->ChangeState(&player->stateMovingLeft);
	}
	if (D_down)
	{
		player->direction = CharacterAnim::Right;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Right;
		player->ChangeState(&player->stateMovingRight);
	}
	if (W_down)
	{
		player->direction = CharacterAnim::Back;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Back;
		player->ChangeState(&player->stateMovingUp);
	}
	if (S_down)
	{
		player->direction = CharacterAnim::Front;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Front;
		player->ChangeState(&player->stateMovingDown);
	}
	//}
}

//StateMovingLeft
void Player::StateMovingLeft::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation((static_cast<int>(player->direction)));
	Engine::GetLogger().LogEvent("Left");
}

void Player::StateMovingLeft::Update(GameObject* object, [[maybe_unused]] double dt)
{
	Player* player = static_cast<Player*>(object);
	bool A_down = player->Left.IsKeyDown();

	if (A_down == true)
	{
		player->SetVelocity(vec2{ -speed, 0 });
	}
}

void Player::StateMovingLeft::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	bool A_down = player->Left.IsKeyDown();
	bool D_down = player->Right.IsKeyDown();
	bool W_down = player->Up.IsKeyDown();
	bool S_down = player->Down.IsKeyDown();

	if (D_down && !W_down && !S_down && !A_down)
	{
		player->direction = CharacterAnim::Right;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Right;
		player->ChangeState(&player->stateMovingRight);
	}
	if (W_down && !S_down && !A_down && !D_down)
	{
		player->direction = CharacterAnim::Back;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Back;
		player->ChangeState(&player->stateMovingUp);
	}
	if (S_down && !A_down && !D_down && !W_down)
	{
		player->direction = CharacterAnim::Front;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Front;
		player->ChangeState(&player->stateMovingDown);
	}
	if (!W_down && !S_down && !A_down && !D_down)
	{
		player->direction = CharacterAnim::None_L;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_None_L;
		player->ChangeState(&player->stateIdle);
	}
}

//StateMovingRight
void Player::StateMovingRight::Enter([[maybe_unused]] GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation((static_cast<int>(player->direction)));
	Engine::GetLogger().LogEvent("Right");
}

void Player::StateMovingRight::Update(GameObject* object, [[maybe_unused]] double dt)
{
	Player* player = static_cast<Player*>(object);
	bool D_down = player->Right.IsKeyDown();

	if (D_down)
	{
		player->SetVelocity(vec2{ speed, 0 });
	}
}

void Player::StateMovingRight::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	bool A_down = player->Left.IsKeyDown();
	bool D_down = player->Right.IsKeyDown();
	bool W_down = player->Up.IsKeyDown();
	bool S_down = player->Down.IsKeyDown();


	if (A_down && !W_down && !S_down && !D_down)
	{
		player->direction = CharacterAnim::Left;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Left;
		player->ChangeState(&player->stateMovingLeft);
	}
	if (W_down && !A_down && !D_down && !S_down)
	{
		player->direction = CharacterAnim::Back;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Back;
		player->ChangeState(&player->stateMovingUp);
	}
	if (S_down && !A_down && !D_down && !W_down)
	{
		player->direction = CharacterAnim::Front;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Front;
		player->ChangeState(&player->stateMovingDown);
	}
	if (!W_down && !S_down && !A_down && !D_down)
	{
		player->direction = CharacterAnim::None_R;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_None_R;
		player->ChangeState(&player->stateIdle);
	}
}

//StateMovingUp
void Player::StateMovingUp::Enter(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation((static_cast<int>(player->direction)));
	Engine::GetLogger().LogEvent("Up");
}

void Player::StateMovingUp::Update(GameObject* object, [[maybe_unused]] double dt)
{
	Player* player = static_cast<Player*>(object);
	bool W_down = player->Up.IsKeyDown();

	if (W_down)
	{
		player->SetVelocity(vec2{ 0, speed });
	}
}

void Player::StateMovingUp::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	bool A_down = player->Left.IsKeyDown();
	bool D_down = player->Right.IsKeyDown();
	bool W_down = player->Up.IsKeyDown();
	bool S_down = player->Down.IsKeyDown();

	if (A_down && !W_down && !S_down && !D_down)
	{
		player->direction = CharacterAnim::Left;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Left;
		player->ChangeState(&player->stateMovingLeft);
	}
	if (D_down && !W_down && !S_down && !A_down)
	{
		player->direction = CharacterAnim::Right;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Right;
		player->ChangeState(&player->stateMovingRight);
	}
	if (S_down && !W_down && !A_down && !D_down)
	{
		player->direction = CharacterAnim::Front;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Front;
		player->ChangeState(&player->stateMovingDown);
	}
	if (!W_down && !S_down && !A_down && !D_down)
	{
		player->direction = CharacterAnim::None_B;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_None_B;
		player->ChangeState(&player->stateIdle);
	}
}

//StateMovingDown
void Player::StateMovingDown::Enter([[maybe_unused]] GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	player->GetGOComponent<Sprite>()->PlayAnimation((static_cast<int>(player->direction)));
	Engine::GetLogger().LogEvent("Down");
}

void Player::StateMovingDown::Update(GameObject* object, [[maybe_unused]] double dt)
{
	Player* player = static_cast<Player*>(object);

	if (player->Down.IsKeyDown() == true)
	{
		player->SetVelocity(vec2{ 0, -speed});
	}
}

void Player::StateMovingDown::TestForExit(GameObject* object)
{
	Player* player = static_cast<Player*>(object);
	bool A_down = player->Left.IsKeyDown();
	bool D_down = player->Right.IsKeyDown();
	bool W_down = player->Up.IsKeyDown();
	bool S_down = player->Down.IsKeyDown();

	if (A_down && !W_down && !S_down && !D_down)
	{
		player->direction = CharacterAnim::Left;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Left;
		player->ChangeState(&player->stateMovingLeft);
	}
	if (D_down && !W_down && !S_down && !A_down)
	{
		player->direction = CharacterAnim::Right;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Right;
		player->ChangeState(&player->stateMovingRight);
	}
	if (W_down && !S_down && !A_down && !D_down)
	{
		player->direction = CharacterAnim::Back;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_Back;
		player->ChangeState(&player->stateMovingUp);
	}
	if (!W_down && !S_down && !A_down && !D_down)
	{
		player->direction = CharacterAnim::None_F;
		if (player->food != nullptr)
			player->direction = CharacterAnim::H_None_F;
		player->ChangeState(&player->stateIdle);
	}
}

