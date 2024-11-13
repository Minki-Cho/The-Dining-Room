#include "FoodBubble.h"
#include "../Engine/Engine.h"

FoodBubble::FoodBubble()
{
}

void FoodBubble::Add(const std::filesystem::path& texturePath)
{
	//bubble
	texture.push_back({ Engine::GetTextureManager().Load(texturePath,false) });

	//burgers
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_cheese.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_lettuce.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_patty.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_tomato.png",true) });

	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_cheese_lettuce.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_patty_lettuce.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_cheese_patty.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_cheese_tomato.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_tomato_lettuce.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_patty_tomato.png",true) });

	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_cheese_lettuce_patty.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_lettuce_patty_tomato.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_cheese_patty_tomato.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_cheese_lettuce_tomato.png",true) });

	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/burger_cheese_lettuce_patty_tomato.png",true) });

	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/coke.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/french_fries.png",true) });
	texture.push_back({ Engine::GetTextureManager().Load("assets/images/foods/ice_cream.png",true) });
}

void FoodBubble::Unload()
{
	texture.clear();
}

void FoodBubble::Draw(vec2 _position, FoodType m_type, FoodType s_type)
{
	texture[0].texturePtr->Draw(mat3<float>::build_translation(_position) * mat3<float>::build_scale(1.5f)); //bubble

	switch (m_type)
	{
	case FoodType::None:
		break;
	case FoodType::C:
		texture[1].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::L:
		texture[2].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::P:
		texture[3].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::T:
		texture[4].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::CL:
		texture[5].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::PL:
		texture[6].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::CP:
		texture[7].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::CT:
		texture[8].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::LT:
		texture[9].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::PT:
		texture[10].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::CLP:
		texture[11].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::PLT:
		texture[12].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::PCT:
		texture[13].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::LCT:
		texture[14].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -5 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	case FoodType::PLCT:
		texture[15].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ -5 , -4 }) * mat3<float>::build_scale(1.5f), vec2{ 0,0 }, vec2{ 40,30 });
		break;
	default:
		break;
	}

	switch (s_type)
	{
	case FoodType::None:
		break;
	case FoodType::COKE:
		texture[16].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ 2 , 46 }) * mat3<float>::build_scale(1.2f), vec2{ 0,0 }, vec2{ 40,40 });
		break;
	case FoodType::FRENCHFRIES:
		texture[17].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ 2 , 45 }) * mat3<float>::build_scale(1.2f), vec2{ 0,0 }, vec2{ 40,40 });
		break;
	case FoodType::ICECREAM:
		texture[18].texturePtr->Draw(mat3<float>::build_translation(_position + vec2{ 2 , 45 }) * mat3<float>::build_scale(1.2f), vec2{ 0,0 }, vec2{ 40,40 });
		break;
	default:
		break;
	}
}

vec2 FoodBubble::Size()
{
	// Doesn't matter all of food size will be same!
	return texture[0].texturePtr->GetSize();;
}
