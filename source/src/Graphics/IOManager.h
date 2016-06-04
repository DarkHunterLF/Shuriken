#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "Errors.h"

class IOManager
{
public:
	static bool readFileToBuffer(std::string filePath, std::vector<unsigned char> &buffer);
};

