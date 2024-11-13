#include "GameScreen.h"
#include "../Engine/Engine.h"

GameScreen::GameScreen() : texturePtr(nullptr)
{
	tile.x = 1100.f / 23.f;
	tile.y = 570.f / 12.f;

	for (int x = 0; x < 23; x++)
	{
		for (int y = 0; y < 12; y++)
		{
			map[x][y] = vec2{ startPos.x + tile.x * x,startPos.y + tile.y * y };
		}
	}
}

void GameScreen::Add(const std::filesystem::path& texturePath)
{
	texturePtr = (Engine::GetTextureManager().Load(texturePath, false));
}

void GameScreen::Unload()
{
	texturePtr = nullptr;
}

void GameScreen::Draw()
{
	texturePtr->Draw(mat3<float>::build_translation(startPos));
}

vec2 GameScreen::Size()
{
	return texturePtr->GetSize();
}

vec2 GameScreen::GetMapPos(int x, int y)
{
	return map[x][y];
}
