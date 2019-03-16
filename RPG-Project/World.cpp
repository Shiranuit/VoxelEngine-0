#include "pch.h"
#include "World.h"


World::World(unsigned int seed)
{
	noise = new PerlinNoise(seed);
	noise2 = new PerlinNoise(rand());
	noise3 = new PerlinNoise(rand());
	chunkShader = new Shader("shaders/cube/cubeFragment.glsl", "shaders/cube/cubeVertex.glsl");

	light.position = glm::vec3(128.0, 96.0, 128.0);
	light.direction = glm::vec3(0.255562, 0.965654, 0.0469043);

	light.ambient = glm::vec3(1.f, 1.f, 1.f);
	light.diffuse = glm::vec3(1.f, 1.f, 1.f);
	light.specular = glm::vec3(1.f, 1.f, 1.f);;
	
	light.constant = 1.0f;
	light.linear = 0.09f;
	light.quadratic = 0.0032f;
	
	light.ambientIntensity = 0.1f;
	light.diffuseIntensity = 0.6f;
	light.specularIntensity = 0.3f;

	light.cutOff = glm::cos(glm::radians(12.5f));
	light.outerCutOff = glm::cos(glm::radians(17.5f));

	light.type = 0;
}


World::~World()
{
	delete noise;
	delete noise2;
	delete noise3;
	delete chunkShader;
	for (int i = 0; i < chunks.size(); i++) {
		Chunk *chunk = chunks[i];
		delete chunk;
	}
	chunks.clear();
	chunks.shrink_to_fit();
}

void World::loadChunk(int x, int z)
{
	float heightMap[256];
	for (int nx = 0; nx < 16; nx++) {
		for (int nz = 0; nz < 16; nz++) {
			int vx = 16 * x + nx;
			int vz = 16 * z + nz;
			heightMap[nx + nz * 16] = noise->noise(vx / 64.0, vz / 64.0, 0) *
				noise2->noise(vx / 48.0, vz / 48.0, 0.8) *
				noise3->noise(vx / 128.0, vz / 128.0, (vx + vz) / 128.0);
		}
	}
	for (int y = 0; y < 16; y++) {
		Chunk *chunk = new Chunk(x * CHUNK_SIZE, y * CHUNK_SIZE, z * CHUNK_SIZE);
		for (int i = 0; i < CHUNK_SIZE; i++) {
			for (int k = 0; k < CHUNK_SIZE; k++) {
				int height = heightMap[i + k * 16] * 256.0 - (y * 16);
				height = height < 16 ? height : 16;
				height = height < 0 ? 0 : height;
				if (height <= 0 && y == 0)
					height = 1;
				for (int j = 0; j < height; j++)
					chunk->setBlock(1, i, j, k);
			}
		}
		chunkBuilder.genMesh(*chunk);
		chunk->setVisible(true);
		chunks.push_back(chunk);
	}
}

void World::render(Camera &camera)
{
	chunkShader->bind();
	chunkShader->setMatrix4f("camera", camera.getProjectionMatrix());
	chunkShader->setVec3f("campos", camera.getPos());
	chunkShader->setVec3f("camdir", camera.getForward());

	light.position = camera.getPos();
	light.direction = camera.getForward();

	//std::cout << camera.getPos().x << " " << camera.getPos().y << " " << camera.getPos().z << std::endl;
	//std::cout << camera.getForward().x << " " << camera.getForward().y << " " << camera.getForward().z << std::endl;
	chunkShader->setLight("lights[0]", &light);
	for (int i = 0; i < chunks.size(); i++)
	{
		Chunk *chunk = chunks[i];
		chunk->render(chunkShader);
	}
}