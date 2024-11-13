#include <iostream>

#include <glCheck.h>
#include <ImGuiHelper.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <imgui.h>

#include "Window.h" //Window
#include "Engine.h"	// GetWindow

namespace
{
    void hint_gl(SDL_GLattr attr, int value)
    {
        if (const auto success = SDL_GL_SetAttribute(attr, value); success != 0)
        {
            std::cerr << "Failed to Set GL Attribute: " << SDL_GetError() << '\n';
        }
    }

    template <typename... Messages> [[noreturn]] void throw_error_message(Messages&&... more_messages)
    {
        std::ostringstream sout;
        (sout << ... << more_messages);
        throw std::runtime_error{ sout.str() };
    }
}

void Window::Init(const char* windowName, int viewportWidth, int viewportHeight)
{
    if (windowName == nullptr || windowName[0] == '\0')
        throw_error_message("App title shouldn't be empty");

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        throw_error_message("Failed to init SDK error: ", SDL_GetError());
    }
    hint_gl(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // hint_gl(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    // hint_gl(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    hint_gl(SDL_GL_DOUBLEBUFFER, true);
    hint_gl(SDL_GL_STENCIL_SIZE, 8);
    hint_gl(SDL_GL_DEPTH_SIZE, 24);
    hint_gl(SDL_GL_RED_SIZE, 8);
    hint_gl(SDL_GL_GREEN_SIZE, 8);
    hint_gl(SDL_GL_BLUE_SIZE, 8);
    hint_gl(SDL_GL_ALPHA_SIZE, 8);
    hint_gl(SDL_GL_MULTISAMPLEBUFFERS, 1);
    hint_gl(SDL_GL_MULTISAMPLESAMPLES, 4);

    viewportWidth = std::max(640, std::min(16384, viewportWidth));
    viewportHeight = std::max(480, std::min(16384, viewportHeight));
    ptrWindow = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, viewportWidth, viewportHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    //SDL_DisplayMode displayMode;
    //SDL_GetCurrentDisplayMode(0, &displayMode);
    //int windowX = (displayMode.w - windowWidth) / 2;
    //int windowY = (displayMode.h - windowHeight) / 2;
    //SDL_SetWindowPosition(ptrWindow, windowX, windowY);
    if (ptrWindow == nullptr)
    {
        throw_error_message("Failed to create window: ", SDL_GetError());
    }

    if (glContext = SDL_GL_CreateContext(ptrWindow); glContext == nullptr)
    {
        throw_error_message("Failed to create opengl context: ", SDL_GetError());
    }

    SDL_GL_MakeCurrent(ptrWindow, glContext);

    if (const auto result = glewInit(); GLEW_OK != result)
    {
        throw_error_message("Unable to initialize GLEW - error: ", glewGetErrorString(result));
    }

    constexpr int ADAPTIVE_VSYNC = -1;
    constexpr int VSYNC = 1;
    if (const auto result = SDL_GL_SetSwapInterval(ADAPTIVE_VSYNC); result != 0)
    {
        SDL_GL_SetSwapInterval(VSYNC);
    }

    ImGuiHelper::Initialize(ptrWindow, glContext);
    SDL_SetWindowResizable(ptrWindow, SDL_FALSE);

    // Define the colors for the hamburger
    Uint32 bunColor = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 224, 123, 57);    // brown
    Uint32 meatColor = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 139, 69, 19);    // dark brown
    Uint32 lettuceColor = SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 124, 252, 0); // green

    // Create a 32x32 surface for the icon
    SDL_Surface* surface = SDL_CreateRGBSurface(0, 32, 32, 32, 0, 0, 0, 0);

    // Fill the surface with the bun color
    SDL_FillRect(surface, NULL, bunColor);

    SDL_Rect meatRect;
    meatRect.x = 0;
    meatRect.y = 11;
    meatRect.w = 32;
    meatRect.h = 11;

    // Fill the meat rectangle with the meat color
    SDL_FillRect(surface, &meatRect, meatColor);

    SDL_Rect lettuceRect;
    lettuceRect.x = 0;
    lettuceRect.y = 17;
    lettuceRect.w = 32;
    lettuceRect.h = 7;


    // Fill the lettuce rectangle with the lettuce color
    SDL_FillRect(surface, &lettuceRect, lettuceColor);

    // Set the window icon
    SDL_SetWindowIcon(ptrWindow, surface);

    // Free the surface after setting the icon
    SDL_FreeSurface(surface);
    

    //int width = 0, height = 0;
    SDL_GL_GetDrawableSize(ptrWindow, &windowWidth, &windowHeight);
    glCheck(glViewport(0, 0, viewportWidth, viewportHeight));

    // anti-aliasing
    glCheck(glEnable(GL_LINE_SMOOTH));
    glCheck(glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST));
    glCheck(glHint(GL_LINE_SMOOTH_HINT, GL_NICEST));
    glCheck(glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST));
    glCheck(glEnable(GL_BLEND));
    glCheck(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    //ptr_window = create_program(width, height);
}

void Window::Update()
{
    SDL_GL_SwapWindow(ptrWindow);
}

void Window::Resize(int newWidth, int newHeight)
{
    windowWidth = newWidth;
    windowHeight = newHeight;
    Engine::GetLogger().LogEvent("Window Resized");
}

vec2 Window::GetSize()
{
    return { static_cast<float>(windowWidth), static_cast<float>(windowHeight) };
}

void Window::Clear()
{
    //glCheck(glClearColor(1, 1, 1, 1));
    glCheck(glClear(GL_COLOR_BUFFER_BIT));
}

void Window::SetBackgroundColor(float r=1, float g=1, float b=1, float a=1)
{
    glCheck(glClearColor(r, g, b, a));
}

void Window::on_window_resized() noexcept
{
    SDL_GL_GetDrawableSize(ptrWindow, &windowWidth, &windowHeight);
    glCheck(glViewport(0, 0, windowWidth, windowHeight));
}

util::owner<SDL_Window*> Window::GetWindowPtr()
{
    return ptrWindow;
}

util::owner<SDL_GLContext> Window::GetGLContext()
{
    return glContext;
}
