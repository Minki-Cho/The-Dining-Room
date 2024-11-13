#include <algorithm>
#include <random>
#include <vector>
#include <Random.h>
#include <imgui.h>
#include <ImGuiHelper.h>
#include <angles.h>

#include "Guest.h"
#include "Guest_Anims.h"
#include "FoodBubble.h"
#include "Money.h"
#include "Number.h"
#include "Timer.h"
#include "Reputation.h"
#include "GameParticles.h"
#include "DayByDay.h"
#include "Unlock.h"
#include "Food.h"
#include "CleanUp.h"
#include "Double_Event.h"

#include "../Engine/Engine.h"
#include "../Engine/Rect.h"
#include "../Engine/Collision.h"
#include "../Engine/GameObject.h"
#include "../Engine/fmod-sound.h"
#include "Sound_lists.h"

Guest::Guest(std::vector<Table*>& table) : GameObject({ 0,100 }),
frequency(0), tableList(table)
{
	Engine::GetGSComponent<Unlock>()->Load("assets/images/lock.png");
	//Load assets
	image = new Sprite("assets/images/characters/guest_1.spt", this);
	images.push_back(image);
	AddGOComponent(image);		//body, 0

	//Initialize Food for drawing
	drawMainFood = new Food();
	drawSideFood = new Food();

	//gauge
	shader = GLShader("changing gauge shader", { {GLShader::VERTEX, "assets/shaders/model_to_ndc_pos2d_clr.vert"}, {GLShader::FRAGMENT, "assets/shaders/basic_vtx_clr_attribute.frag"} });
	CreateChangingGaugeQuad();

	star_texture.push_back({ Engine::GetTextureManager().Load("assets/images/characters/one.png", false) });
	star_texture.push_back({ Engine::GetTextureManager().Load("assets/images/characters/two.png", false) });

	Sprite* back_hair = nullptr;
	Sprite* front_hair = nullptr;

	hair = util::random(0, 13);
	switch (hair)	//back hair, 1 | front hair, 2
	{
	case 0:
		back_hair = new Sprite("assets/images/characters/hair/0_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/0_front.spt", this);
		break;
	case 1:
		back_hair = new Sprite("assets/images/characters/hair/1_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/1_front.spt", this);
		break;
	case 2:
		back_hair = new Sprite("assets/images/characters/hair/2_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/2_front.spt", this);
		break;
	case 3:
		back_hair = new Sprite("assets/images/characters/hair/3_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/3_front.spt", this);
		break;
	case 4:
		back_hair = new Sprite("assets/images/characters/hair/4_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/4_front.spt", this);
		break;
	case 5:
		back_hair = new Sprite("assets/images/characters/hair/4_back_2.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/4_front.spt", this);
		break;
	case 6:
		back_hair = new Sprite("assets/images/characters/hair/6_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/6_front.spt", this);
		break;
	case 7:
		back_hair = new Sprite("assets/images/characters/hair/7_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/7_front.spt", this);
		break;
	case 8:
		back_hair = new Sprite("assets/images/characters/hair/8_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/8_front.spt", this);
		break;
	case 9:
		back_hair = new Sprite("assets/images/characters/hair/9_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/9_front.spt", this);
		break;
	case 10:
		back_hair = new Sprite("assets/images/characters/hair/10_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/10_front.spt", this);
		break;
	case 11:
		back_hair = new Sprite("assets/images/characters/hair/11_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/11_front.spt", this);
		break;
	case 12:
		back_hair = new Sprite("assets/images/characters/hair/12_back.spt", this);
		front_hair = new Sprite("assets/images/characters/hair/12_front.spt", this);
		break;
	default:
		break;
	}
	images.push_back(back_hair);
	AddGOComponent(back_hair);
	images.push_back(front_hair);
	AddGOComponent(front_hair);
	back_hair = nullptr;
	front_hair = nullptr;


	cloth = util::random(1, 11);
	if(hair == 0) { cloth = 0; }
	switch (cloth)		//cloth, 3
	{
	case 0:
		image = new Sprite("assets/images/characters/clothes/0.spt", this);
		break;
	case 1:
		image = new Sprite("assets/images/characters/clothes/1.spt", this);
		break;
	case 2:
		image = new Sprite("assets/images/characters/clothes/2.spt", this);
		break;
	case 3:
		image = new Sprite("assets/images/characters/clothes/3.spt", this);
		break;
	case 4:
		image = new Sprite("assets/images/characters/clothes/4.spt", this);
		break;
	case 5:
		image = new Sprite("assets/images/characters/clothes/5.spt", this);
		break;
	case 6:
		image = new Sprite("assets/images/characters/clothes/6.spt", this);
		break;
	case 7:
		image = new Sprite("assets/images/characters/clothes/7.spt", this);
		break;
	case 8:
		image = new Sprite("assets/images/characters/clothes/8.spt", this);
		break;
	case 9:
		image = new Sprite("assets/images/characters/clothes/9.spt", this);
		break;
	case 10:
		image = new Sprite("assets/images/characters/clothes/10.spt", this);
		break;
	default:
		break;
	}
	images.push_back(image);
	AddGOComponent(image);


	shoes = util::random(1, 8);
	if(hair == 0) { shoes = 0; }
	switch (shoes)		//shoes, 4
	{
	case 0:
		image = new Sprite("assets/images/characters/shoes/0.spt", this);
		break;
	case 1:
		image = new Sprite("assets/images/characters/shoes/1.spt", this);
		break;
	case 2:
		image = new Sprite("assets/images/characters/shoes/2.spt", this);
		break;
	case 3:
		image = new Sprite("assets/images/characters/shoes/3.spt", this);
		break;
	case 4:
		image = new Sprite("assets/images/characters/shoes/4.spt", this);
		break;
	case 5:
		image = new Sprite("assets/images/characters/shoes/5.spt", this);
		break;
	case 6:
		image = new Sprite("assets/images/characters/shoes/6.spt", this);
		break;
	case 7:
		image = new Sprite("assets/images/characters/shoes/7.spt", this);
		break;
	default:
		break;
	}
	images.push_back(image);
	AddGOComponent(image);

	//Set position
	SetPosition({ 180, 250 });
	currState = &stateMoving;
	currState->Enter(this);

	// The frequency of the customer later it will depends on the reputation!
	frequency = util::random(3, 10);


	//Set main order randomly
	if (Engine::GetGSComponent<Unlock>()->GetLettuce() == false
		&& Engine::GetGSComponent<Unlock>()->GetCheese() == false
		&& Engine::GetGSComponent<Unlock>()->GetTomato() == false) // burger - only patty & sidemenu
	{
		std::vector<FoodType> menu = { FoodType::P, FoodType::P, FoodType::P };
		mainFood = new Food(mainFood->RandomFood(menu));
	}

	else if (Engine::GetGSComponent<Unlock>()->GetLettuce() == true
		&& Engine::GetGSComponent<Unlock>()->GetCheese() == false
		&& Engine::GetGSComponent<Unlock>()->GetTomato() == false) // lettuce Unlock & sidemenu
	{
		std::vector<FoodType> menu = { FoodType::L, FoodType::L, FoodType::P, FoodType::P,
										FoodType::PL, FoodType::PL };
		mainFood = new Food(mainFood->RandomFood(menu));
	}

	else if (Engine::GetGSComponent<Unlock>()->GetLettuce() == false
		&& Engine::GetGSComponent<Unlock>()->GetCheese() == true
		&& Engine::GetGSComponent<Unlock>()->GetTomato() == false) // cheese Unlock & sidemenu
	{
		std::vector<FoodType> menu = { FoodType::C, FoodType::C, FoodType::P, FoodType::P,
										FoodType::CP, FoodType::CP };
		mainFood = new Food(mainFood->RandomFood(menu));
	}
	
	else if (Engine::GetGSComponent<Unlock>()->GetLettuce() == false
		&& Engine::GetGSComponent<Unlock>()->GetCheese() == false
		&& Engine::GetGSComponent<Unlock>()->GetTomato() == true) // tomato Unlock & sidemenu
	{
		std::vector<FoodType> menu = { FoodType::T, FoodType::T, FoodType::P, FoodType::P,
										FoodType::PT, FoodType::PT };
		mainFood = new Food(mainFood->RandomFood(menu));
	}

	else if (Engine::GetGSComponent<Unlock>()->GetLettuce() == true
		&& Engine::GetGSComponent<Unlock>()->GetCheese() == false
		&& Engine::GetGSComponent<Unlock>()->GetTomato() == true) // lettuce and tomato Unlock & sidemenu
	{
		std::vector<FoodType> menu = { FoodType::T, FoodType::T, FoodType::P, FoodType::P, FoodType::L, FoodType::L,
										FoodType::PT, FoodType::PT, FoodType::LT, FoodType::LT, FoodType::PL, FoodType::PL,
										FoodType::PLT, FoodType::PLT };
		mainFood = new Food(mainFood->RandomFood(menu));
	}

	else if (Engine::GetGSComponent<Unlock>()->GetLettuce() == true
		&& Engine::GetGSComponent<Unlock>()->GetCheese() == true
		&& Engine::GetGSComponent<Unlock>()->GetTomato() == false) // lettuce and cheese Unlock & sidemenu
	{
		std::vector<FoodType> menu = { FoodType::C, FoodType::C, FoodType::P, FoodType::P, FoodType::L, FoodType::L,
										FoodType::CP, FoodType::CP, FoodType::CL, FoodType::CL, FoodType::PL, FoodType::PL,
										FoodType::CLP, FoodType::CLP };
		mainFood = new Food(mainFood->RandomFood(menu));
	}

	else if (Engine::GetGSComponent<Unlock>()->GetLettuce() == false
		&& Engine::GetGSComponent<Unlock>()->GetCheese() == true
		&& Engine::GetGSComponent<Unlock>()->GetTomato() == true) // tomato and cheese Unlock & sidemenu
	{
		std::vector<FoodType> menu = { FoodType::C, FoodType::C, FoodType::P, FoodType::P, FoodType::T, FoodType::T,
										FoodType::CP, FoodType::CP, FoodType::CT, FoodType::CT, FoodType::PT, FoodType::PT,
										FoodType::PCT, FoodType::PCT };
		mainFood = new Food(mainFood->RandomFood(menu));
	}
	
	else   //all ingredients are unlocked & sidemenu
	{
		mainFood = new Food(static_cast<FoodType>(util::random(static_cast<int>(FoodType::P), static_cast<int>(FoodType::PLCT))));
	}

	//Set side order randomly
	std::vector<FoodType> side_menu = { FoodType::None, FoodType::COKE, FoodType::FRENCHFRIES };
	if (Engine::GetGSComponent<Unlock>()->GetIcecream() == true) //ice cream
		side_menu.push_back(FoodType::ICECREAM);
	sideFood = new Food(sideFood->RandomFood(side_menu));

	//Food for drawing
	drawMainFood->SetType(mainFood->GetType());
	drawSideFood->SetType(sideFood->GetType());
}

Guest::~Guest()
{
	tableList.clear();
}

void Guest::Update(double dt)
{
	GameObject::Update(dt);
	GameObject::UpdatePosition(GetVelocity());

	//if (Engine::GetGSComponent<Timer>()->HasEnded())
	//{
	//	SetDestroyed(true);
	//}

	if (Engine::GetGSComponent<DayByDay>()->GetDrawbool() == true)
		SetDestroyed(true);
}

bool Guest::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Player
		|| objectBType == GameObjectType::WorkBenches
		|| objectBType == GameObjectType::Guest)
	{
		return true;
	}
	return false;
}

void Guest::ResolveCollision(GameObject* objectB)
{
	rect3 guestRect = GetGOComponent<RectCollision>()->GetWorldCoorRect();
	rect3 collideRect = objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect();

	switch (objectB->GetObjectType())
	{
	case GameObjectType::Guest:
		if (guestRect.Right() > collideRect.Left() && guestRect.Right() < collideRect.Right()) // Right
		{
			UpdatePosition(vec2{ collideRect.Left() - guestRect.Right(),0.0 });
			SetVelocity({ 0, 0 });
			isWaiting = true;
		}
		break;

	case GameObjectType::WorkBenches:
		if (objectB->GetObjectTypeName() == "Counter")
		{
			isColideCounter = true;
		}
		isColideWorkBenches = true;
		break;

	case GameObjectType::Player:
		if (isPaying == false && drawMoney == true)
		{
			drawMoney = false;
			isPaying = true;
		}
		break;

	default:
		break;
	}
	if (objectB->GetObjectType() == GameObjectType::Player)
	{
		isCollide_player = true;
	}
	else
	{
		isCollide_player = false;
	}
}

void Guest::Draw(mat3<float> displayMatrix)
{
	if (isDrawing == true)
	{
		if (animNumber == 0 || animNumber == 4)	//forward
		{
			images[1]->Draw(displayMatrix * GetMatrix());	//back hair
			images[0]->Draw(displayMatrix * GetMatrix());	//body
			images[4]->Draw(displayMatrix * GetMatrix());	//shoes
			images[3]->Draw(displayMatrix * GetMatrix());	//cloth
			images[2]->Draw(displayMatrix * GetMatrix());	//front hair
		}
		else if (animNumber == 1 || animNumber == 5)	//back
		{
			images[2]->Draw(displayMatrix * GetMatrix());	//front hair
			images[0]->Draw(displayMatrix * GetMatrix());	//body
			images[4]->Draw(displayMatrix * GetMatrix());	//shoes
			images[3]->Draw(displayMatrix * GetMatrix());	//cloth
			images[1]->Draw(displayMatrix * GetMatrix());	//back hair
		}
		else if (animNumber == 8)	//eating
		{
			images[0]->Draw(displayMatrix * GetMatrix());	//body
			images[4]->Draw(displayMatrix * GetMatrix());	//shoes
			images[3]->Draw(displayMatrix * GetMatrix());	//cloth
			images[1]->Draw(displayMatrix * GetMatrix());	//back hair
			images[2]->Draw(displayMatrix * GetMatrix());	//front hair
		}
		else   //left or right
		{
			images[0]->Draw(displayMatrix * GetMatrix());	//body
			images[4]->Draw(displayMatrix * GetMatrix());	//shoes
			images[3]->Draw(displayMatrix * GetMatrix());	//cloth
			images[1]->Draw(displayMatrix * GetMatrix());	//back hair
			images[2]->Draw(displayMatrix * GetMatrix());	//front hair
		}
	}
	if (drawMenu == true)
	{
		Engine::GetGameStateManager().GetGSComponent<FoodBubble>()->Draw(GetPosition() + vec2{ -25, 110 }, drawMainFood->GetType(), drawSideFood->GetType());
	}
	if (drawMoney == true)
	{
		Engine::GetGameStateManager().GetGSComponent<Money>()->Draw({ GameObject::GetPosition().x - 26, GameObject::GetPosition().y + 113 });
	}
	if (drawAngry == true)
	{
		angry_texture->Draw(mat3<float>::build_translation(vec2{ GetPosition().x,GetPosition().y + 60.f }));
	}
	if (finishedPaying == true)
	{
		Engine::GetGSComponent<CleanUp>()->Draw({ GameObject::GetPosition() });
	}
	if (stateCleanUp.isone == true)
	{
		star_texture[0].texturePtr->Draw(mat3<float>::build_translation(GameObject::GetPosition()));
	}
	if (stateCleanUp.istwo == true)
	{
		star_texture[1].texturePtr->Draw(mat3<float>::build_translation(GameObject::GetPosition()));
	}

	if (isTable == true)
		DrawGauge(vec2{ GetPosition().x - 35.f,GetPosition().y - 20.f });
}

void Guest::SetIsGetFood()
{
	isGetFood = true;
}

void Guest::SetIsRightMenu()
{
	isRightMenu = true;
}

bool Guest::GetIsGetFood()
{
	return isGetFood;
}

bool Guest::GetIsPaying()
{
	return isPaying;
}

bool Guest::GetIsColideCounter()
{
	return isColideCounter;
}

bool Guest::GetIsRightMenu()
{
	return isRightMenu;
}

void Guest::CreateChangingGaugeQuad()
{
	constexpr std::array positions = { vec2{0.f,1.f}, vec2{0.f,0.f}, vec2{1.f,1.f}, vec2{1.f,0.f} };
	constexpr std::array colors = { color3{0.4f, 1.f, 0.05f}, color3{0.4f, 1.f, 0.05f}, color3{0.4f, 1.f, 0.05f}, color3{0.4f, 1.f, 0.05f} };
	constexpr std::array<unsigned char, 4> indices = { 0, 1, 2, 3 };

	GLAttributeLayout position_layout;
	position_layout.component_type = GLAttributeLayout::Float;
	position_layout.component_dimension = GLAttributeLayout::_2;
	position_layout.normalized = false;
	position_layout.vertex_layout_location = 0;
	position_layout.stride = sizeof(vec2);
	position_layout.offset = 0;
	position_layout.relative_offset = 0;

	GLAttributeLayout color_layout;
	color_layout.component_type = GLAttributeLayout::Float;
	color_layout.component_dimension = GLAttributeLayout::_3;
	color_layout.normalized = false;
	color_layout.vertex_layout_location = 1;
	color_layout.stride = sizeof(color3);
	color_layout.offset = 0;
	color_layout.relative_offset = 0;

	gaugeShape.AddVertexBuffer(GLVertexBuffer(std::span{ positions }), { position_layout });
	gaugeShape.AddVertexBuffer(GLVertexBuffer(std::span{ colors }), { color_layout });
	gaugeShape.SetPrimitivePattern(GLPrimitive::TriangleStrip);
	GLIndexBuffer index_buffer(indices);
	gaugeShape.SetIndexBuffer(std::move(index_buffer));
}

namespace
{
	std::span<const float, 3 * 3> to_span(const mat3<float>& m)
	{
		return std::span<const float, 3 * 3>(&m.elements[0][0], 9);
	}
	std::span<const float, 3> to_span(const color3& c)
	{
		return std::span<const float, 3>(&c.elements[0], 3);
	}
}

#include <iostream>
void Guest::DrawGauge(vec2 startPos)
{
	mat3 translation{ mat3<float>::build_translation(startPos.x - (1280.f - Engine::GetWindow().GetSize().x) / 2.f,startPos.y - (720.f - Engine::GetWindow().GetSize().y) / 2.f) };
	mat3<float> scale_ = mat3<float>::build_scale((10.f - static_cast<float>(timer)) * 7.f, 10);
	mat3 to_bottom_left{ mat3<float>::build_translation(-Engine::GetWindow().GetSize().x / 2,-Engine::GetWindow().GetSize().y / 2) };
	const mat3<float> model_to_world = to_bottom_left * translation * scale_;

	mat3 extent = mat3<float>::build_scale(2.f / 1280.f, 2.f / 720.f);
	const mat3 model_to_ndc = extent * model_to_world;

	shader.Use();
	shader.SendUniform("uModelToNDC", to_span(model_to_ndc));
	gaugeShape.Use();
	GLDrawIndexed(gaugeShape);
	gaugeShape.Use(false);
	shader.Use(false);
}

const vec2& Guest::GetPosition() const
{
	return GameObject::GetPosition();
}

//StateMoving
void Guest::StateMoving::Enter(GameObject* object)
{
	Guest* guest = static_cast<Guest*>(object);
	guest->animNumber = 7;
	for (auto& i : guest->images)
	{
		i->PlayAnimation(guest->animNumber);	//move_right
	}
	Engine::GetLogger().LogEvent("Moving");
}

void Guest::StateMoving::Update(GameObject* object, double dt)
{
	Guest* guest = static_cast<Guest*>(object);
	if (guest->isAppear == true && guest->GetPosition().x < limit)
	{
		guest->SetVelocity(vec2{ static_cast<float>(speed * dt), 0 });
	}
}

void Guest::StateMoving::TestForExit(GameObject* object)
{
	Guest* guest = static_cast<Guest*>(object);

	//if customer is in front of counter
	if (guest->GetPosition().x >= limit)
	{
		guest->SetVelocity(vec2{ 0, 0 });
		guest->isAppear = false;
		guest->drawMenu = true;
		guest->ChangeState(&guest->stateWaiting);
	}

	//if another customer is in front of this customer
	if (guest->isWaiting == true && guest->GetPosition().x < limit)
	{
		guest->SetVelocity(vec2{ 0, 0 });
		guest->drawMenu = true;
		guest->ChangeState(&guest->stateWaiting);
	}
}

//StateWaiting
void Guest::StateWaiting::Enter(GameObject* object)
{
	Guest* guest = static_cast<Guest*>(object);
	guest->animNumber = 0;	//none_forward
	for (auto& i : guest->images)
	{
		i->PlayAnimation(guest->animNumber);
	}
}

void Guest::StateWaiting::Update(GameObject* object, double dt)
{
	Guest* guest = static_cast<Guest*>(object);

	timer += dt;
	if (timer > 12)
	{
		guest->drawAngry = true;
		Engine::GetGSComponent<Reputation>()->Decrease(4);
		timer = 0;
	}
	//if another customer in front of this customer get the food and goes to table
	if (guest->isAppear == true)
	{
		guest->SetVelocity(vec2{ static_cast<float>(speed * dt), 0 });
	}
	if (guest->GetPosition().x >= limit)
	{
		guest->SetVelocity(vec2{ 0, 0 });
		guest->isAppear = false;
		guest->ChangeState(&guest->stateWaiting);
	}

	if (guest->isColideCounter)
	{
		if (guest->counter->getGivenFood1().GetType() != FoodType::Count)
			guest->drawMainFood->SetType(FoodType::None);
		if (guest->counter->getGivenFood2().GetType() != FoodType::Count)
			guest->drawSideFood->SetType(FoodType::None);

		//If no side menu
		if (guest->sideFood->GetType() == FoodType::None && guest->counter->getCount() == 1)
		{
			if (guest->counter->getGivenFood1().GetType() == guest->mainFood->GetType())
			{
				guest->isGetFood = true;
				guest->isRightMenu = true;
			}
			else
			{
				guest->isGetFood = true;
				guest->isRightMenu = false;
			}
			guest->counter->setCount();
		}
		else if (guest->counter->getCount() == 2)
		{
			if (guest->counter->getGivenFood1().GetType() == guest->mainFood->GetType()
				&& guest->counter->getGivenFood2().GetType() == guest->sideFood->GetType())
			{
				guest->isGetFood = true;
				guest->isRightMenu = true;
			}
			else
			{
				guest->isGetFood = true;
				guest->isRightMenu = false;
			}
			guest->counter->setCount();
		}
	}
}

void Guest::StateWaiting::TestForExit(GameObject* object)
{
	Guest* guest = static_cast<Guest*>(object);
	if (guest->isGetFood == true)
	{
		for (auto& t : guest->tableList)
		{
			if (t->GetEmpty() == true)
			{
				guest->drawAngry = false;
				if (guest->isRightMenu == true)
				{
					Engine::GetGameStateManager().GetGSComponent<SparkleEmitter>()->Emit(30, guest->GetPosition() + vec2{ 0,guest->GetGOComponent<Sprite>()->GetFrameSize().y / 2 }, vec2{ 0,1.f }, vec2{ 0,100.f }, util::HALF_PI<float>);
				}
				else if (guest->isRightMenu == false)
				{
					Engine::GetGSComponent<Reputation>()->Decrease(5);
				}
				guest->ChangeState(&guest->stateIdle_table);
				break;
			}
			guest->ChangeState(&guest->stateWaiting);
		}
	}
}

//StateTable
void Guest::StateTable::Enter(GameObject* object)
{
	Guest* guest = static_cast<Guest*>(object);
	guest->SetVelocity(vec2{ 0, 0 });

	std::random_device rd;
	std::mt19937_64 g(rd());
	std::shuffle(begin(guest->tableList), end(guest->tableList), g);
	for (auto& t : guest->tableList)
	{
		if (t->GetEmpty())
		{
			guest->SetPosition(t->GetPosition() + vec2(-20, 0));
			t->SetEmpty(false);
			break;
		}
	}
	guest->animNumber = 8;	//none_forward
	for (auto& i : guest->images)
	{
		i->PlayAnimation(guest->animNumber);
	}

	guest->isAppear = false;
	guest->drawMenu = false;
	guest->isColideCounter = false;
	guest->isTable = true;
}

void Guest::StateTable::Update([[maybe_unused]] GameObject* object, double dt)
{
	Guest* guest = static_cast<Guest*>(object);
	guest->timer += dt;
}

void Guest::StateTable::TestForExit(GameObject* object)
{
	Guest* guest = static_cast<Guest*>(object);
	if (guest->timer > 10)
	{
		guest->isTable = false;
		guest->ChangeState(&guest->statePaying);
	}
}

void Guest::StatePaying::Enter(GameObject* object)
{
	Guest* guest = static_cast<Guest*>(object);
	guest->drawMoney = true;
	guest->animNumber = 0;	//none_forward
	for (auto& i : guest->images)
	{
		i->PlayAnimation(guest->animNumber);
	}
}

void Guest::StatePaying::Update([[maybe_unused]] GameObject* object, double dt)
{
	Guest* guest = static_cast<Guest*>(object);
	timer += dt;
	if (timer > 10)
	{
		guest->drawAngry = true;
		Engine::GetGSComponent<Reputation>()->Decrease(4);
		timer = 0;
	}
}

void Guest::StatePaying::TestForExit(GameObject* object)
{
	Guest* guest = static_cast<Guest*>(object);
	// The customer will leave the store after paying.
	if (guest->isPaying == true)
	{
		for (auto& t : guest->tableList)
		{
			if (guest->DoesCollideWith(t))
			{
				if (!t->GetEmpty())
				{
					guest->drawAngry = false;
					t->SetEmpty(true);

					if (guest->isRightMenu == true)
					{
						Engine::GetGSComponent<Reputation>()->Increase(1);
						if (Engine::GetGSComponent<Double_Event>()->GetIsEvent() == true)
						{
							SoundManager::sharedManager()->play(static_cast<int>(game_sounds::MONEY), false);
							Engine::GetGSComponent<Number>()->UpdateNumber((guest->mainFood->GetPrice() + guest->sideFood->GetPrice()) * 2);
						}
						else
						{
							SoundManager::sharedManager()->play(static_cast<int>(game_sounds::MONEY), false);
							Engine::GetGSComponent<Number>()->UpdateNumber(guest->mainFood->GetPrice() + guest->sideFood->GetPrice());
						}
					}
					else if (guest->isRightMenu == false)
					{
						if (Engine::GetGSComponent<Double_Event>()->GetIsEvent() == true)
						{
							SoundManager::sharedManager()->play(static_cast<int>(game_sounds::MONEY), false);
							Engine::GetGSComponent<Number>()->UpdateNumber(8);
						}
						else
						{
							SoundManager::sharedManager()->play(static_cast<int>(game_sounds::MONEY), false);
							Engine::GetGSComponent<Number>()->UpdateNumber(4);
						}
					}
					guest->finishedPaying = true;
					guest->images.erase(guest->images.begin(), guest->images.end());
					guest->images.clear();
					Engine::GetGameStateManager().GetGSComponent<MoneyEmitter>()->Emit(30, guest->GetPosition() + vec2{ 0,guest->GetGOComponent<Sprite>()->GetFrameSize().y / 2 }, vec2{ 0,1.f }, vec2{ 0,100.f }, util::HALF_PI<float>);
					guest->isDrawing = false;
					//guest->ClearGOComponents();
					delete guest->angry_texture;
					guest->ChangeState(&guest->stateCleanUp);
					//guest->SetDestroyed(true);
					break;
				}
			}
		}
	}
}

void Guest::StateCleanUp::Enter(GameObject* /*object*/)
{
}

void Guest::StateCleanUp::Update(GameObject* object, double /*dt*/)
{
	Guest* guest = static_cast<Guest*>(object);
	for (auto& t : guest->tableList)
	{
		if (guest->DoesCollideWith(t) && guest->finishedPaying == true)
		{
			t->SetEmpty(false);
			if (Push.IsKeyReleased() == true && t->GetCheck() == true)
			{
				count_space++;
			}
			if (count_space == 1)
			{
				isone = true;
				istwo = false;
			}
			if (count_space == 2)
			{
				isone = false;
				istwo = true;
			}
			if (count_space == 3)
			{
				t->SetEmpty(true);
				guest->finishedPaying = false;
			}
		}
	}
}

void Guest::StateCleanUp::TestForExit(GameObject* object)
{
	Guest* guest = static_cast<Guest*>(object);

	if (guest->finishedPaying == false)
	{
		guest->SetDestroyed(true);
		guest->ClearGOComponents();
	}
}