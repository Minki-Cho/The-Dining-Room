#include "Table.h"
#include "../Engine/Engine.h"

//for test
#include <iostream>

Table::Table(rect3 rect, Player* _player)
	: WorkBench(rect, _player)
{
	position = vec2{ rect.point1.x,rect.point1.y };
	texturePtr = Engine::GetTextureManager().Load("assets/images/map/table.png", false);
}

void Table::Check()
{
	if (this->GetCheck() == true && player->GetIsOnTask() == true)
	{
		/* Get money, and send data to show current money in UI */
		this->SetCheckFalse();
	}
}

void Table::Update([[maybe_unused]] double dt)
{
}

void Table::Draw()
{
	texturePtr->Draw(mat3<float>::build_translation(position));
}

bool Table::GetEmpty()
{
	return isEmpty;
}

void Table::SetEmpty(bool _setValue)
{
	isEmpty = _setValue;
}
