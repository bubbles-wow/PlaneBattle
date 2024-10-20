#pragma once
#ifndef FILE_OUTPUT_H
#define FILE_OUTPUT_H

#include "ILoggerOutput.h"

class FileOutput : public ILoggerOutput {
private:
	static std::ofstream file;
public:
	inline static void close() {
		FileOutput::file.close();
	}
	inline static void setFilePath(const std::string& filePath) {
		FileOutput::file.close();
		FileOutput::file.open(filePath + "\\log.txt", std::ios::out | std::ios::app);
	}
	inline void output(const std::string& msg) override {
		FileOutput::file << msg << std::endl;
	}
};

#endif // FILE_OUTPUT_H