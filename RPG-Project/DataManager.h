#pragma once

#include <GL/glew.h>
#include <iomanip>

class DataManager
{
public:
	static uint32_t byte4ToInt(uint8_t x, uint8_t y, uint8_t z, uint8_t w);
	static uint8_t* intToByte4(uint32_t val);
};

