#include "TrashCan.h"
#include "../Engine/Engine.h"

TrashCan::TrashCan(rect3 rect, Player* _player) : WorkBench(rect, _player)
{
	position = vec2{ rect.point1.x, rect.point1.y };
	texturePtr = Engine::GetTextureManager().Load("assets/images/map/trashcan.png", false);
}

void TrashCan::Check()
{
	if (this->GetCheck() == true && player->GetIsOnTask() == true)
	{
		if (&player->GetFood() != nullptr)
		{
			player->SetFoodToNull();
		}
		this->SetCheckFalse();
	}
}

void TrashCan::Update([[maybe_unused]]double dt) {}

void TrashCan::Draw()
{
	texturePtr->Draw(mat3<float>::build_translation(position));
}
