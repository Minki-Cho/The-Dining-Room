#pragma once
#include <string>
#include <fstream> //file output
#include <chrono> //time

class Logger
{
public:
	enum class Severity
	{
		Verbose,		// This option is for minor messages, which could be useful 
		Debug,			// This should only be used when you are currently trying to debug something
		Event,			// These are general events, such as key press, exit state, enter state, enter state finish
		Error,			// This is for an error, such as an asset is not found
	};

	Logger(Severity severity, bool useConsole, std::chrono::system_clock::time_point start_time);
	~Logger();

	void LogError(std::string text);
	void LogEvent(std::string text);
	void LogDebug(std::string text);
	void LogVerbose(std::string text);

private:
	void Log(Severity, std::string displayText);
	double GetSecondsSinceStart();

	std::ofstream outStream;
	Severity minLevel;
	std::chrono::system_clock::time_point startTime;
};