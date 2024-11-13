#pragma once
#include <memory>
#include <chrono> //time

#include "GameStateManager.h" //get statemanger
#include "Input.h" //get input
#include "Window.h" //get window
#include "Logger.h" //get logger
#include "TextureManager.h" //get texturemanager

class Engine
{
public:
    Engine();
    ~Engine() = default;

    static Engine& Instance() { static Engine instance; return instance; }
    static Logger& GetLogger() { return Instance().logger; };
    static Input& GetInput() { return Instance().input; }
    static Window& GetWindow() { return Instance().window; }
    static GameStateManager& GetGameStateManager() { return Instance().gameStateManager; }
    static TextureManager& GetTextureManager() { return Instance().textureManager; }

    template<typename T>
    static T* GetGSComponent() { return GetGameStateManager().GetGSComponent<T>(); }

    void Init(const char* windowName);
    void Shutdown();
    void Update();
    bool HasGameEnded();
    void AddSpriteFont(const std::filesystem::path& fileName);
    bool getGameFinish() { return gameFinish; }
    void UpdateGameObjects(double dt);
private:
    std::chrono::system_clock::time_point lastTick;
    std::chrono::system_clock::time_point fpsCalcTime;
    int frameCount;
    bool gameFinish;
    Logger logger;
    GameStateManager gameStateManager;
    Input input;
    Window window;
    TextureManager textureManager;
    std::chrono::system_clock::time_point now;
    double dt=0;
    static constexpr double Target_FPS = 60.0;
    static constexpr int FPS_IntervalSec = 5;
    static constexpr int FPS_IntervalFrameCount = static_cast<int>(FPS_IntervalSec * Target_FPS);
};