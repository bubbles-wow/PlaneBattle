#pragma once
#ifndef CONSOLE_OUTPUT_H
#define CONSOLE_OUTPUT_H

#include "ILoggerOutput.h"

class ConsoleOutput : public ILoggerOutput {
public:
	inline void output(const std::string& msg) override {
		*(Logger::getLogStream()) << msg << std::endl;
	}
};

#endif // CONSOLE_OUTPUT_H
