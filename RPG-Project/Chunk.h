#ifndef CHUNK_H
#define CHUNK_H
#include "Mesh.h"
#include "IndexedModel.h"
#include "Transform.h"
#include "Shader.h"
#include "Block.h"

constexpr auto CHUNK_SIZE = 16;

class Chunk
{
public:
	Chunk(int x, int y, int z);
	~Chunk();

	void setBlock(unsigned int id, unsigned int x, unsigned int y, unsigned int z);
	unsigned int getBlock(unsigned int x, unsigned int y, unsigned int z);
	Mesh &getMesh();
	void setVisible(bool state);
	bool isVisible();
	void render(Shader *shader);

private:
	Mesh mesh;
	uint32_t data[CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE] = { 0 };
	Transform pos;
	unsigned int blockCount;
	bool visible;

	bool toggleFace(unsigned int x, unsigned int y, unsigned int z, Block::Side side);
	bool toggleFace(unsigned int pos, Block::Side side);
	unsigned int getPos(unsigned int x, unsigned int y, unsigned int z);
};
#endif
