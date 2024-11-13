#include "Money.h"
#include "../Engine/Engine.h"

Money::Money()
{
}

void Money::Add(const std::filesystem::path& texturePath)
{
	texture.push_back({ Engine::GetTextureManager().Load(texturePath,false) });
}

void Money::Unload()
{
	texture.clear();
}

void Money::Draw(vec2 position)
{
	for (auto& m : texture)
	{
		m.texturePtr->Draw(mat3<float>::build_translation(position));
	}
}

vec2 Money::Size()
{
	// Doesn't matter all of food size will be same!
	return texture[0].texturePtr->GetSize();;
}
