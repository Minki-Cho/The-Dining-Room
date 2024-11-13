#pragma once
#include <GLShader.h>
#include <GLVertexArray.h>
#include "../Engine/Component.h"
#include "../Engine/Texture.h"

enum class Satisfaction
{
	Best,
	Good,
	Normal,
	Bad,
	Worst
};

class Reputation : public Component
{
private:
	Texture* face;
	Texture* bar;
	float gauge;
	Satisfaction satisfaction;
	vec2 texturePos;

	GLShader shader;
	GLVertexArray gaugeShape;

	void CreateChangingGaugeQuad();
public:
	Reputation(float value);
	void Update(double) override;
	void DrawFace(vec2 startPos);
	void DrawGauge(vec2 startPos);

	void Increase(float value)
	{
		if (gauge < 100)
			gauge += value;
		if (gauge > 100)
			gauge = 100;
	};
	void Decrease(float value)
	{
		if (gauge > 0)
			gauge -= value;
		if (gauge < 0)
			gauge = 0;
	};
	float getGauge() { return gauge; }
};