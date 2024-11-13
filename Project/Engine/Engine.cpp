#include "Engine.h" //Engine
#include <random>

Engine::Engine() : frameCount(0), lastTick(std::chrono::system_clock::now()),
gameFinish(false),
#ifdef _DEBUG				
logger(Logger::Severity::Debug, true, lastTick)
#else 						
logger(Logger::Severity::Event, false, lastTick)
#endif
{}

void Engine::Init(const char* windowName)
{
	logger.LogEvent("Engine Init");
	window.Init(windowName, 1280, 720);
	fpsCalcTime = lastTick;
	std::mt19937 rng(std::random_device{}());
}

void Engine::Shutdown()
{
	logger.LogEvent("Engine Shutdown");
	//SDL_Quit();
}

void Engine::Update()
{
	now = { std::chrono::system_clock::now() };
	dt = std::chrono::duration<double>(now - lastTick).count();

	//33.33milliseconds
	if (dt >= 1 / Engine::Target_FPS)
	{
		Engine::logger.LogVerbose("Engine Update");
		lastTick = now;

		if (++frameCount > Engine::FPS_IntervalFrameCount)
		{
			double averageFrameRate = frameCount / std::chrono::duration<double>(now - fpsCalcTime).count();
			Engine::logger.LogEvent("FPS: " + std::to_string(averageFrameRate));
			frameCount = 0;
			fpsCalcTime = now;
		}
		gameStateManager.Update(dt);
		input.Update();
		window.Update();
	}
}

bool Engine::HasGameEnded()
{
	return gameStateManager.HasGameEnded();
}

void Engine::AddSpriteFont(const std::filesystem::path&)
{
	//fonts.push_back(fileName);
}