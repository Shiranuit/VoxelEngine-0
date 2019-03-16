#pragma once
#include <vector>
#include "Chunk.h"
#include "ChunkMeshBuilder.h"
#include "Shader.h"
#include "PerlinNoise.h"
#include "Camera.h"
#include "Light.h"

class World
{
public:
	World(unsigned int seed);
	virtual ~World();
	void loadChunk(int x, int z);
	void render(Camera &camera);

private:
	std::vector<Chunk *> chunks;
	ChunkMeshBuilder chunkBuilder;
	PerlinNoise *noise;
	PerlinNoise *noise2;
	PerlinNoise *noise3;
	Light light;
	Shader *chunkShader;
};