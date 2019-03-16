#include "pch.h"
#include "Chunk.h"
#include <vector>
#include "Block.h"



Chunk::Chunk(int _x, int _y, int _z)
{
	blockCount = 0;
	visible = false;
	pos.addPos(_x, _y, _z);
}

Chunk::~Chunk()
{
}

unsigned int Chunk::getPos(unsigned int x, unsigned int y, unsigned int z)
{
	return x | (y << 4) | (z << 8);
}

bool Chunk::toggleFace(unsigned int x, unsigned int y, unsigned int z, Block::Side side)
{
	if (x < CHUNK_SIZE && y < CHUNK_SIZE && z < CHUNK_SIZE) {
		unsigned int pos = getPos(x, y, z);
		if (data[pos] > 0)
			Block::toggleBlockFace(data + pos, side);
		else
			return false;
		return true;
	}
	return false;
}

bool Chunk::toggleFace(unsigned int pos, Block::Side side)
{
	if (data[pos] > 0)
		Block::toggleBlockFace(data + pos, side);
	else
		return false;
	return true;
}

void Chunk::setBlock(unsigned int id, unsigned int x, unsigned int y, unsigned int z)
{
	if (x < CHUNK_SIZE && y < CHUNK_SIZE && z < CHUNK_SIZE) {
		unsigned int pos = getPos(x, y, z);
		if (data[pos] == 0 && id > 0) {
			data[pos] = 0x3F000000 | id;
			blockCount += 1;
			if (toggleFace(x - 1, y,     z,     Block::Side::RIGHT))
				toggleFace(pos,     Block::Side::LEFT);

			if (toggleFace(x + 1, y,     z,     Block::Side::LEFT))
				toggleFace(pos,     Block::Side::RIGHT);
			
			if (toggleFace(x,     y,     z - 1, Block::Side::FRONT))
				toggleFace(pos,     Block::Side::BACK);

			if (toggleFace(x,     y,     z + 1, Block::Side::BACK))
				toggleFace(pos,     Block::Side::FRONT);

			if (toggleFace(x,     y - 1, z,     Block::Side::TOP))
				toggleFace(pos,     Block::Side::BOTTOM);

			if (toggleFace(x,     y + 1, z,     Block::Side::BOTTOM))
				toggleFace(pos,     Block::Side::TOP);

		} else if (data[pos] > 0 && id == 0) {
			data[pos] = id;
			blockCount -= 1;
			toggleFace(x - 1, y, z, Block::Side::RIGHT);
			toggleFace(x + 1, y, z, Block::Side::LEFT);
			toggleFace(x, y, z - 1, Block::Side::FRONT);
			toggleFace(x, y, z + 1, Block::Side::BACK);
			toggleFace(x, y - 1, z, Block::Side::TOP);
			toggleFace(x, y + 1, z, Block::Side::BOTTOM);
		}
	}
}

unsigned int Chunk::getBlock(unsigned int x, unsigned int y, unsigned int z)
{
	if (x < CHUNK_SIZE && y < CHUNK_SIZE && z < CHUNK_SIZE) {
		unsigned int pos = x | (y << 4) | (z << 8);

		return data[pos];
	}
	return 0;
}

Mesh &Chunk::getMesh()
{
	return mesh;
}

void Chunk::render(Shader *shader)
{
	if (visible && blockCount > 0) {
		shader->setMatrix4f("position", pos.computeMatrix());
		mesh.render();
	}
}

void Chunk::setVisible(bool state)
{
	visible = state;
}

bool Chunk::isVisible()
{
	return visible;
}