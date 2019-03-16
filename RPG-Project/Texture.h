#pragma once
#include <iomanip>
#include "stb_image.h"

class Texture
{
public:
	Texture(const std::string &filepath);
	Texture(const char *filepath);
	virtual ~Texture();

private:
	unsigned int texture;
};

