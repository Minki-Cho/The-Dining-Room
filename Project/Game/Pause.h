#pragma once

#include "../Engine/Component.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"

class Pause : public Component
{
public:
	Pause();

	void Draw();
	void Update(double dt) override;
	void Unload();
	void SetDraw(bool type);
	bool GetDrawbool();
private:
	std::vector<Texture*> texture;
	bool Isdraw;
};