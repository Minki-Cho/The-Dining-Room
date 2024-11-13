#pragma once

#include "../Engine/Component.h"
#include "../Engine/Input.h"
#include "../Engine/Texture.h"
#include "../Engine/Button.h"

#include "Result.h"
#include "Market.h"

class DayByDay : public Component
{
public:
	DayByDay();

	void Draw();
	void Update(double dt) override;
	void Unload();
	void SetDraw(bool type);
	bool GetDrawbool();
	bool IsTomorrow()
	{
		return Istomorrow;
	}
	bool getIsDraw() { return Isdraw; }
	bool GetResultDraw() { return result_draw; }
	bool GetMarketDraw() { return market_draw; }
	void SetResultDraw(bool isResult) { result_draw = isResult; }
	void SetMarketDraw(bool isMarket) { market_draw = isMarket; }
	void SetTomorrow(bool state) { Istomorrow = state; }

private:
	Texture* texture;
	double timer;
	bool Isdraw;
	bool result_draw;
	bool market_draw;
	bool Istomorrow = true;
};