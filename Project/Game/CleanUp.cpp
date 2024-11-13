#include "CleanUp.h"
#include "../Engine/Engine.h"

CleanUp::CleanUp()
{
    texture.push_back({ Engine::GetTextureManager().Load("assets/images/trash.png",true) });
}

void CleanUp::Unload()
{
    texture.clear();
}

void CleanUp::Draw(vec2 _position)
{
    texture[0].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , 3 }) * mat3<float>::build_scale(1.0f), vec2{ 0,0 }, vec2{ 40,49 });
}

vec2 CleanUp::Size()
{
    return texture[0].texturePtr->GetSize();;
}
