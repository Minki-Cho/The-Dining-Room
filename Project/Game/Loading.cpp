#include "Loading.h"
#include "../Engine/Engine.h"


void Loading::Add(const std::filesystem::path& texturePath)
{
	texture.push_back({ Engine::GetTextureManager().Load(texturePath, false) });
}

void Loading::Unload()
{
	texture.clear();
}

void Loading::Draw()
{
	for (auto& map : texture)
	{
		map.texturePtr->Draw(mat3<float>::build_translation(startPos));
	}
}

vec2 Loading::Size()
{
	return texture[0].texturePtr->GetSize();
}