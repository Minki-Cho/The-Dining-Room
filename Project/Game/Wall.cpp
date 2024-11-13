#include "Wall.h"
#include "../Engine/Rect.h"
#include "../Engine/Collision.h"

Wall::Wall(rect3 rect) : GameObject(vec2{ 0,0 })
{
	AddGOComponent(new RectCollision(rect, this));
}