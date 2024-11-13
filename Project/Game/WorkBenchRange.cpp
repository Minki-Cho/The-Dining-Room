#include "WorkBenchRange.h"
#include "../Engine/Engine.h"
#include "HighLight.h"
WorkBenchRange::WorkBenchRange(WorkBench* _workbench, Direction _direction)
	: GameObject(vec2{ 0,0 }), workbench(_workbench), direction(_direction)
{
	rect = workbench->GetRect();
	size = vec2{ rect.Size().width, rect.Size().height };

	rect3 rangeRect{};

	switch (direction)
	{
	case Direction::Left:
		rangeRect = { vec3{rect.point1.x - size.width + 5.f, rect.point1.y + 5.f, 1.0f}, vec3{rect.point1.x - 5.f, rect.point2.y - 5.f, 1.0f} };
		AddGOComponent(new RectCollision(rangeRect, this));
		break;
	case Direction::Right:
		rangeRect = { vec3{rect.point2.x + 5.f, rect.point1.y + 5.f, 1.0f}, vec3{rect.point2.x + size.width - 5.f, rect.point2.y - 5.f, 1.0f} };
		AddGOComponent(new RectCollision(rangeRect, this));
		break;
	case Direction::Top:
		rangeRect = { vec3{rect.point1.x + 5.f, rect.point2.y + 5.f, 1.0f}, vec3{rect.point2.x - 5.f, rect.point2.y + size.height - 5.f, 1.0f} };
		AddGOComponent(new RectCollision(rangeRect, this));
		break;
	case Direction::Bottom:
		rangeRect = { vec3{rect.point1.x + 5.f, rect.point1.y - size.height + 5.f, 1.0f}, vec3{rect.point2.x - 5.f, rect.point1.y - 5.f, 1.0f} };
		AddGOComponent(new RectCollision(rangeRect, this));
		break;
	}
};

vec2 WorkBenchRange::GetSize()
{
	return size;
}

void WorkBenchRange::Update(double)
{
	if (Engine::GetGSComponent<HighLight>()->GetIsDraw() == true)
	{
		Engine::GetGSComponent<HighLight>()->SetIsDrawing(false);
	}
}

bool WorkBenchRange::CanCollideWith(GameObjectType objectBType)
{
	if (objectBType == GameObjectType::Player)
	{
		return true;
	}
	
	return false;
}

void WorkBenchRange::ResolveCollision(GameObject* objectB)
{
	if (objectB->GetObjectType() == GameObjectType::Player)
	{		
		//if (GetGOComponent<RectCollision>()->DoesCollideWith(objectB->GetPosition()))
		//if (GetGOComponent<RectCollision>()->DoesCollideWith(objectB->GetPosition() + 
		//	vec2{objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Size().x / 6,
		//	objectB->GetGOComponent<RectCollision>()->GetWorldCoorRect().Size().y / 4}))
		//{
		//	Engine::GetGSComponent<HighLight>()->SetIsDrawing(true);
		//	Engine::GetGSComponent<HighLight>()->SetPos({ workbench->GetPosition() });
		//	workbench->SetCheckTrue();
		//	workbench->Check();
		//}
		if (GetGOComponent<RectCollision>()->DoesCollideWith(objectB->GetPosition() +
			vec2{ 0,objectB->GetGOComponent<Sprite>()->GetFrameSize().y / 4 }
		))
		{
			Engine::GetGSComponent<HighLight>()->SetIsDrawing(true);
			Engine::GetGSComponent<HighLight>()->SetPos({ workbench->GetPosition() });
			workbench->SetCheckTrue();
			workbench->Check();
		}
		else
		{
			workbench->SetCheckFalse();
		}
	}
}