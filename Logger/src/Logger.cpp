#include <pch.h>
#include <Logger.h>
#include <ConsoleOutput.h>
#include <FileOutput.h>

// 定义静态成员
Logger* Logger::instance = nullptr;
ILoggerOutput* Logger::consoleOutput = new ConsoleOutput();
ILoggerOutput* Logger::fileOutput = new FileOutput();
std::mutex Logger::logMutex;
std::ostream* Logger::logStream = &std::cout;

void Logger::output(const std::string& msg, const std::string& className, LogLevel level) {
	std::lock_guard<std::mutex> guard(Logger::logMutex);

	auto now = std::chrono::system_clock::now();
	time_t currentTime = std::chrono::system_clock::to_time_t(now);
	tm localTime;
	localtime_s(&localTime, &currentTime);
	auto localTimePlus = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;

	std::stringstream ss;
	ss << "[" << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S") << '.' << std::setw(6) << std::setfill('0') << localTimePlus.count() << "]";

	if (!className.empty()) {
		ss << "[" << className << "] ";
	}
	else {
		ss << " ";
	}

	switch (level) {
	case LogLevel::INFO:
		ss << "INFO: " << msg;
		break;
	case LogLevel::WARNING:
		ss << "WARNING: " << msg;
		break;
	case LogLevel::ERR:
		ss << "ERROR: " << msg;
		break;
	}

	Logger::consoleOutput->output(ss.str());
	if (level == LogLevel::ERR) {
		Logger::fileOutput->output(ss.str());
	}
}
