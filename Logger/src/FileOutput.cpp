#include <pch.h>
#include <FileOutput.h>

std::ofstream FileOutput::file = std::ofstream("log.txt", std::ios::out | std::ios::app);