#include "Logger.h"
#include "LoggerApi.h"
#include "FileOutput.h"

void logFunc(const std::string& msg, const std::string& className, LogLevel level) {
	Logger::output(msg, className, level);
}

void initLogFilePath(const std::string& filePath) {
	FileOutput::setFilePath(filePath);
}

void initLogStream(std::ostream& stream) {
    Logger::setLogStream(stream);
}

void release() {
    FileOutput::close();
    Logger::releaseLogger();
}