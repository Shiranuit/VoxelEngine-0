#pragma once
#include "Transform.h"
#include "Texture.h"
#include "Shader.h"
#include "Timer.h"
#include <iomanip>
#include <vector>

class MagicCircleRenderer
{
public:
	MagicCircleRenderer(const char **files, int count, Shader *shader);
	virtual ~MagicCircleRenderer();
	void init(long long time, unsigned int size);
	void render();

private:
	Timer timer;
	std::vector<Texture> textures;
	Transform transform;
	Shader *shader;
	long long time;
	unsigned int size;
	GLuint *VAOS;
	GLuint *BUFFERS;
};

