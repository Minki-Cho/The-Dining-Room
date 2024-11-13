#pragma once
#include <GLShader.h>
#include <GLVertexArray.h>
#include "..\Engine\Texture.h" 
#include "..\Engine\Component.h"

class Timer2 : public Component
{
public:
    Timer2(int time);
    void Update(double dt) override;
    void Cheat();
    void Draw(vec2 startPos);
    bool HasEnded();
    void Reset(float time);
    float getTime() { return timer; }

    void CreateChaningCircle();

private:
    const int timerSet;
    float timer;
    Texture background;
    Texture frame;

    GLShader shader;
    GLVertexArray timerShape;
    bool isTimeOut;
};