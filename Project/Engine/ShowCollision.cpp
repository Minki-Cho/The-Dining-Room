#include "ShowCollision.h" //ShowCollision

ShowCollision::ShowCollision(InputKey::Keyboard keyToUse) : showCollisionKey(keyToUse), enabled(false) {}

void ShowCollision::Update(double)
{
	if (showCollisionKey.IsKeyReleased() == true)
	{
		enabled = !enabled;
	}
}

bool ShowCollision::IsEnabled()
{
	return enabled;
}