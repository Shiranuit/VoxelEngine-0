#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "IndexedModel.h"
#include "DataManager.h"

class Block
{
public:
	Block();
	virtual ~Block();

	enum Side {
		FRONT,
		BACK,
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
	};

	static Side side;

	static void genVertexs(IndexedModel &model, uint8_t x, uint8_t y, uint8_t z, unsigned int block);
	static void addFace(IndexedModel &model, uint8_t x, uint8_t y, uint8_t z, const Side blockface, const uint8_t *face);
	static unsigned int getBlockColor(unsigned int block);
	static bool hasBlockFace(unsigned int block, Side side);
	static void toggleBlockFace(unsigned int *block, Side side);
};
#endif