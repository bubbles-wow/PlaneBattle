#pragma once
#ifndef I_LOGGER_OUTPUT_H
#define I_LOGGER_OUTPUT_H

#include "pch.h"

class ILoggerOutput {
public:
	virtual void output(const std::string& msg) = 0;
	virtual ~ILoggerOutput() = default;
};

#endif // I_LOGGER_OUTPUT_H