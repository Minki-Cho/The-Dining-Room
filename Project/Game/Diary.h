#pragma once

#include "../Engine/Component.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/Button.h"

class Diary : public Component
{
public:
	Diary();

	void Draw();
	void Update(double dt) override;
	void Unload();
	void SetDraw(bool type);
	bool GetDrawbool();
	bool IsTomorrow()
	{
		return Istomorrow;
	}
	bool GetNextClicked() { return isNextClicked; }
	void SetTomorrow(bool state) { Istomorrow = state; }
	void UpdateIndex();
private:
	std::vector<Texture*> texture;
	double timer;
	bool Isdraw;
	bool Istomorrow = true;
	int DiaryRandomized;

	enum class ButtonTypes
	{
		Play,
		HowToPlay,
		Credit,
	};
	Button Next;
	bool isNextClicked = false;
};