#include "Kitchen.h"
#include "../Engine/Engine.h"


void Kitchen::Add(const std::filesystem::path& texturePath)
{
	texture.push_back({ Engine::GetTextureManager().Load(texturePath, false) });
}

void Kitchen::Unload()
{
	texture.clear();
}

void Kitchen::Draw()
{
	for (auto &map : texture)
	{
		map.texturePtr->Draw(mat3<float>::build_translation(startPos));
	}
}

vec2 Kitchen::Size()
{
	return texture[0].texturePtr->GetSize();
}