#include "pch.h"
#include "Block.h"
#include <iostream>


Block::Block()
{
}


Block::~Block()
{
}

const uint8_t frontFace[] = {
	0, 1, 1,
	1, 1, 1,
	0, 0, 1,
	1, 0, 1,
};

const uint8_t backFace[] = {
	1, 1, 0,
	0, 1, 0,
	1, 0, 0,
	0, 0, 0,
};

const uint8_t leftFace[] = {
	0, 1, 0,
	0, 1, 1,
	0, 0, 0,
	0, 0, 1,
};

const uint8_t rightFace[] = {
	1, 1, 1,
	1, 1, 0,
	1, 0, 1,
	1, 0, 0,
};

const uint8_t topFace[] = {
	0, 1, 0,
	1, 1, 0,
	0, 1, 1,
	1, 1, 1,
};

const uint8_t bottomFace[] = {
	0, 0, 1,
	1, 0, 1,
	0, 0, 0,
	1, 0, 0,
};

uint8_t encodeNormal(int8_t x, int8_t y, int8_t z)
{
	uint8_t val = 0;

	val |= x;
	val |= y << 1;
	val |= z << 2;
	if (x < 0 || y < 0 || z < 0)
		val |= 1 << 3;
	return val;
}

void Block::addFace(IndexedModel &model, uint8_t x, uint8_t y, uint8_t z, const Side blockface, const uint8_t *face)
{
	uint8_t normal = 0;
	if (blockface == FRONT)
		normal = encodeNormal(0, 0, 1);

	if (blockface == BACK)
		normal = encodeNormal(0, 0, -1);

	if (blockface == LEFT)
		normal = encodeNormal(-1, 0, 0);

	if (blockface == RIGHT)
		normal = encodeNormal(1, 0, 0);

	if (blockface == TOP)
		normal = encodeNormal(0, 1, 0);

	if (blockface == BOTTOM)
		normal = encodeNormal(0, -1, 0);

	for (int i = 0, index = 0; i < 4; ++i)
	{
		int nx = face[index++] + x;
		int ny = face[index++] + y;
		int nz = face[index++] + z;
		model.m_pos[model.total_pos++] = DataManager::byte4ToInt(nx, ny, nz, normal);
		model.m_col[model.total_col++] = DataManager::byte4ToInt(0 / (i + 1), 200 / (0 + 1), 0 / (i + 1), 255);
	}
	

	model.m_indices[model.total_id++] = model.indices_count;
	model.m_indices[model.total_id++] = model.indices_count + 2;
	model.m_indices[model.total_id++] = model.indices_count + 1;

	model.m_indices[model.total_id++] = model.indices_count + 2;
	model.m_indices[model.total_id++] = model.indices_count + 3;
	model.m_indices[model.total_id++] = model.indices_count + 1;
	model.indices_count += 4;
}

void Block::genVertexs(IndexedModel &model, uint8_t x, uint8_t y, uint8_t z, unsigned int block)
{
	if (hasBlockFace(block, FRONT))
		addFace(model, x, y, z, FRONT, frontFace);

	if (hasBlockFace(block, BACK))
		addFace(model, x, y, z, BACK, backFace);

	if (hasBlockFace(block, LEFT))
		addFace(model, x, y, z, LEFT, leftFace);

	if (hasBlockFace(block, RIGHT))
		addFace(model, x, y, z, RIGHT, rightFace);

	if (hasBlockFace(block, TOP))
		addFace(model, x, y, z, TOP, topFace);

	if (hasBlockFace(block, BOTTOM))
		addFace(model, x, y, z, BOTTOM, bottomFace);
}

unsigned int Block::getBlockColor(unsigned int block)
{
	return block & 0x00FFFFFF;
}

bool Block::hasBlockFace(unsigned int block, Side side)
{
	return ((block >> (24 + side)) & 1) == 1;
}

void Block::toggleBlockFace(unsigned int *block, Side side)
{
	*block ^= (1 << (24 + side));
}