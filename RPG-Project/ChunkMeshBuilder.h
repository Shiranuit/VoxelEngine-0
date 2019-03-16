#pragma once

#include "IndexedModel.h"
#include "Chunk.h"
#include "Block.h"

class ChunkMeshBuilder
{
public:
	ChunkMeshBuilder();
	virtual ~ChunkMeshBuilder();
	void genMesh(Chunk &chunk);

private:
	IndexedModel *model;
};

