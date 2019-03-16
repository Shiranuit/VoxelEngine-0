#include "pch.h"
#include "ChunkMeshBuilder.h"


ChunkMeshBuilder::ChunkMeshBuilder()
{
	model = new IndexedModel(CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE * 6);
}


ChunkMeshBuilder::~ChunkMeshBuilder()
{
	model->clear();
	delete model;
}

void ChunkMeshBuilder::genMesh(Chunk &chunk)
{
	for (unsigned int y = 0; y < CHUNK_SIZE; y++) {
		for (unsigned int x = 0; x < CHUNK_SIZE; x++) {
			for (unsigned int z = 0; z < CHUNK_SIZE; z++) {
				unsigned int block = chunk.getBlock(x, y, z);
				if (block > 0) {
					Block::genVertexs(*model, x, y, z, block);
				}
			}
		}
	}
	chunk.getMesh().initModel(*model);
	model->clear();

}