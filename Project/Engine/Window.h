#pragma once
#include <string> //std::string

#include <owner.h>
#include "vec2.h"
#include "color3.h"

struct SDL_Window;
typedef void* SDL_GLContext;

class Window
{
public:
    void Init(const char* windowName, int viewportWidth, int viewportHeight);
    void Update();
    void on_window_resized() noexcept;

    //vec2
    void Resize(int newWidth, int newHeight);
    vec2 GetSize();
    void Clear();
    void SetBackgroundColor(float r, float g, float b, float a);
    util::owner<SDL_Window*> GetWindowPtr();
    util::owner<SDL_GLContext> GetGLContext();
private:
    int   windowWidth{ 0 };
    int   windowHeight{ 0 };

    util::owner<SDL_Window*>   ptrWindow = nullptr;
    util::owner<SDL_GLContext> glContext = nullptr;
};