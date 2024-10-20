

#include "LogLevel.h"
#include "ILoggerOutput.h"

class Logger {
private:
	static ILoggerOutput* consoleOutput;
	static ILoggerOutput* fileOutput;
	static Logger* instance;
	static std::mutex logMutex;
	static std::ostream* logStream;
public:
	inline static std::ostream* getLogStream() {
		return logStream;
	}
	inline static void setLogStream(std::ostream& stream) {
		logStream = &stream;
	}
	inline static void releaseLogger() {
		delete consoleOutput;
		delete fileOutput;
		delete instance;
	}
	static void output(const std::string& msg, const std::string& className = "", LogLevel level = LogLevel::INFO);
};

