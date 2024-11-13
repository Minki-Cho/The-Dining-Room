#include <angles.h>
#include <Random.h>
#include <glCheck.h>

#include "Timer.h"
#include "Sound_lists.h"
#include "../Engine/fmod-sound.h"
#include "..\Engine\Engine.h"

//for test
#include <iostream>

Timer::Timer(int time) : timer(static_cast<float>(time)), timerSet(time),
background("assets/images/timer_back.png", false), frame("assets/images/timer_frame.png", false), isTimeOut(false)
{
    shader = GLShader("changing circle shader", { {GLShader::VERTEX, "assets/shaders/model_to_ndc_pos2d_clr.vert"}, {GLShader::FRAGMENT, "assets/shaders/basic_vtx_clr_attribute.frag"} });

    std::vector<vec2> pos_vtx(timerSet + 2);
    pos_vtx[0] = vec2{ 0.0f,0.0f };
    for (int i = 0; i <= timerSet; i++)
    {
        pos_vtx[i + 1] = vec2{ cos(util::to_radians(360.0f / timerSet) * i),sin(util::to_radians(360.0f / timerSet) * i) };
    }

    timerShape.SetVertexCount(static_cast<int>(pos_vtx.size()));

    GLAttributeLayout position;
    position.component_dimension = GLAttributeLayout::_2;
    position.component_type = GLAttributeLayout::Float;
    position.normalized = false;
    position.offset = 0;
    position.relative_offset = 0;
    position.stride = sizeof(vec2);
    position.vertex_layout_location = 0;

    timerShape.AddVertexBuffer(GLVertexBuffer(std::span{ pos_vtx }), { position });
    timerShape.SetPrimitivePattern(GLPrimitive::TriangleFan);

    CreateChaningCircle();
}

void Timer::Update(double dt)
{
	timer -= static_cast<float>(dt);
    if (timer < 8 && isTimeOut == false)
    {
        SoundManager::sharedManager()->play(static_cast<int>(game_sounds::TIMEOUT), false);
        isTimeOut = true;
    }
}

void Timer::Cheat()
{
    timer -= 10;
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

void Timer::Draw(vec2 startPos)
{
    background.Draw(mat3<float>::build_translation(startPos - background.GetSize() / 2.f));

    //mat3<float> translation = mat3<float>::build_translation(startPos.x, startPos.y);
    mat3 translation{ mat3<float>::build_translation(startPos.x - (1280.f - Engine::GetWindow().GetSize().x) / 2.f,startPos.y - (720.f - Engine::GetWindow().GetSize().y) / 2.f) };
    mat3<float> scale = mat3<float>::build_scale(40, -40);
    mat3 to_bottom_left{ mat3<float>::build_translation(-Engine::GetWindow().GetSize().x / 2,-Engine::GetWindow().GetSize().y / 2) };
    const mat3<float> model_to_world = to_bottom_left * translation * scale;

    //mat3<float> extent = mat3<float>::build_scale(2 / Engine::GetWindow().GetSize().x, 2 / Engine::GetWindow().GetSize().y);
    mat3 extent = mat3<float>::build_scale(2.f / 1280.f, 2.f / 720.f);
    const mat3 model_to_ndc = extent * model_to_world;

    shader.Use();
    shader.SendUniform("uModelToNDC", to_span(model_to_ndc));
    timerShape.Use();
    if(HasEnded() == false)
        glCheck(glDrawArrays(timerShape.GetPrimitivePattern(), 0, timerShape.GetVertexCount() - (timerSet - static_cast<int>(timer))));
    timerShape.Use(false);
    shader.Use(false);

    frame.Draw(mat3<float>::build_translation(startPos - background.GetSize()/2.f));
}

bool Timer::HasEnded()
{
	return (timer < 0);
}

void Timer::Reset(float time)
{
	timer = time;
    isTimeOut = false;
}

void Timer::CreateChaningCircle()
{
    std::vector<color3> color(timerSet + 2);
    color[0] = color3{ 1.f,1.f,0.45f };
    for (int i = 1; i <= timerSet; i++)
    {
        color[i] = color3{ 1.f,1.f,0.45f };
    }
    color[timerSet + 1] = color[1];

    GLAttributeLayout color_layout;
    color_layout.component_type = GLAttributeLayout::Float;
    color_layout.component_dimension = GLAttributeLayout::_3;
    color_layout.normalized = false;
    color_layout.stride = sizeof(color3);
    color_layout.offset = 0;
    color_layout.relative_offset = 0;
    color_layout.vertex_layout_location = 1;

    timerShape.AddVertexBuffer(GLVertexBuffer(std::span{color}), {color_layout});
}