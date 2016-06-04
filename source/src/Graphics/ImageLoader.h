#pragma once
#include "GLTexture.h"
#include <string>
#include "picoPNG.h"
#include <vector>
#include "IOManager.h"
#include "Errors.h"
#include <GL\glew.h>

class ImageLoader
{
public:
	static GLTexture loadPNG(std::string filePath);
};