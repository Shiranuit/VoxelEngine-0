#include "pch.h"
#include "DataManager.h"

uint32_t DataManager::byte4ToInt(uint8_t x, uint8_t y, uint8_t z, uint8_t w)
{
	return ((uint32_t)x) |
			(((uint32_t)y) << 8) |
			(((uint32_t)z) << 16) |
			(((uint32_t)w) << 24);
}

uint8_t* DataManager::intToByte4(uint32_t val)
{
	uint8_t data[4];
	data[0] = val & 0xFF;
	data[1] = (val >> 8) & 0xFF;
	data[2] = (val >> 16) & 0xFF;
	data[3] = (val >> 24) & 0xFF;
	return data;
}