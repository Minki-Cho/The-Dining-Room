#include "Reputation.h"
#include "../Engine/Engine.h"
#include "../Engine/GameObject.h"
#include "mat3.h"

Reputation::Reputation(float value) : gauge(value), satisfaction(Satisfaction::Normal)
{
	//face
	face = Engine::GetTextureManager().Load("assets/images/satisfaction.png", true);

	//gauge
	shader = GLShader("changing gauge shader", { {GLShader::VERTEX, "assets/shaders/model_to_ndc_pos2d_clr.vert"}, {GLShader::FRAGMENT, "assets/shaders/basic_vtx_clr_attribute.frag"} });

	//gauge bar
	bar = Engine::GetTextureManager().Load("assets/images/reputation_bar.png", false);

	constexpr std::array positions = { vec2{0.f,1.f}, vec2{0.f,0.f}, vec2{1.f,1.f}, vec2{1.f,0.f} };
	constexpr std::array<unsigned char, 4> indices = { 0, 1, 2, 3 };

	GLAttributeLayout position_layout;
	position_layout.component_type = GLAttributeLayout::Float;
	position_layout.component_dimension = GLAttributeLayout::_2;
	position_layout.normalized = false;
	position_layout.vertex_layout_location = 0;
	position_layout.stride = sizeof(vec2);
	position_layout.offset = 0;
	position_layout.relative_offset = 0;

	gaugeShape.AddVertexBuffer(GLVertexBuffer(std::span{ positions }), { position_layout });
	gaugeShape.SetPrimitivePattern(GLPrimitive::TriangleStrip);
	GLIndexBuffer index_buffer(indices);
	gaugeShape.SetIndexBuffer(std::move(index_buffer));

	CreateChangingGaugeQuad();
}

void Reputation::Update(double)
{
	if (gauge >= 0 && gauge < 30)
	{
		satisfaction = Satisfaction::Worst;
	}
	else if (gauge >= 30 && gauge < 50)
	{
		satisfaction = Satisfaction::Bad;
	}
	else if (gauge >= 50 && gauge < 80)
	{
		satisfaction = Satisfaction::Normal;
	}
	else if (gauge >= 80 && gauge < 90)
	{
		satisfaction = Satisfaction::Good;
	}
	else if (gauge >= 90 && gauge <= 100)
	{
		satisfaction = Satisfaction::Best;
	}
}

void Reputation::DrawFace(vec2 startPos)
{
	face->Draw(mat3<float>::build_translation(startPos), vec2{ static_cast<int>(satisfaction) * 64.f,0 }, vec2{ 64,64 });
}

namespace
{
	std::span<const float, 3 * 3> to_span(const mat3<float>& m)
	{
		return std::span<const float, 3 * 3>(&m.elements[0][0], 9);
	}
	std::span<const float, 3> to_span(const color3& c)
	{
		return std::span<const float, 3>(&c.elements[0], 3);
	}
}

void Reputation::DrawGauge(vec2 startPos)
{
	mat3 translation{ mat3<float>::build_translation(startPos.x - (1280.f - Engine::GetWindow().GetSize().x) / 2.f,startPos.y - (720.f - Engine::GetWindow().GetSize().y) / 2.f) };
	mat3<float> scale = mat3<float>::build_scale(300, 30);
	mat3 to_bottom_left{ mat3<float>::build_translation(-Engine::GetWindow().GetSize().x / 2,-Engine::GetWindow().GetSize().y / 2) };
	const mat3<float> model_to_world = to_bottom_left * translation * scale;

	mat3 extent = mat3<float>::build_scale(2.f / 1280.f, 2.f / 720.f);
	const mat3 model_to_ndc = extent * model_to_world;

	shader.Use();
	shader.SendUniform("uModelToNDC", to_span(extent * to_bottom_left * mat3<float>::build_translation(startPos.x - (1280.f - Engine::GetWindow().GetSize().x) / 2.f, startPos.y - (720.f - Engine::GetWindow().GetSize().y) / 2.f) * mat3<float>::build_scale(gauge * 3, 30)));
	gaugeShape.Use();
	GLDrawIndexed(gaugeShape);
	gaugeShape.Use(false);
	shader.Use(false);
	
	bar->Draw(mat3<float>::build_translation(vec2{ startPos.x-30, startPos.y-30 }));
}

void Reputation::CreateChangingGaugeQuad()
{
	constexpr std::array colors = { color3{0.4f, 1.f, 0.05f}, color3{0.4f, 1.f, 0.05f}, color3{0.4f, 1.f, 0.05f}, color3{0.4f, 1.f, 0.05f} };

	GLAttributeLayout color_layout;
	color_layout.component_type = GLAttributeLayout::Float;
	color_layout.component_dimension = GLAttributeLayout::_3;
	color_layout.normalized = false;
	color_layout.vertex_layout_location = 1;
	color_layout.stride = sizeof(color3);
	color_layout.offset = 0;
	color_layout.relative_offset = 0;

	gaugeShape.AddVertexBuffer(GLVertexBuffer(std::span{ colors }), { color_layout });
}