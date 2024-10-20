#pragma once
#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif // LOGGER_EXPORTS

#include <string>

#include "LogLevel.h"

extern "C" LOGGER_API void logFunc(const std::string& msg, const std::string& className, LogLevel level);
extern "C" LOGGER_API void initLogFilePath(const std::string& filePath);
extern "C" LOGGER_API void initLogStream(std::ostream& stream);
extern "C" LOGGER_API void release();