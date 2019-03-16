#include "pch.h"
#include "MagicCircleRenderer.h"


MagicCircleRenderer::MagicCircleRenderer(const char **files, int count, Shader *shader)
{
	time = 0;
	size = 0;
	textures.reserve(count);
	this->shader = shader;

	VAOS = (GLuint *)malloc(sizeof(GLuint) * (count));
	BUFFERS = (GLuint *)malloc(sizeof(GLuint) * (count));

	glGenVertexArrays(count, VAOS);
	glGenBuffers(count, BUFFERS);

	GLfloat vertexs[] = {
		0.f, 0.f, 0.f,
		1.f, 0.f, 0.f,
		0.f, 0.f, 1.f,
		1.f, 0.f, 1.f,	
	};

	for (int i = 0; i < count; i++) {
		glBindVertexArray(VAOS[i]);
		glBindBuffer(GL_ARRAY_BUFFER, BUFFERS[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(&vertexs[0]) * 12, &vertexs[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		textures.push_back(Texture(files[i]));
		glBindVertexArray(0);
	}
}


MagicCircleRenderer::~MagicCircleRenderer()
{
}

void MagicCircleRenderer::init(long long time, unsigned int size)
{
	this->time = time;
	this->size = size;
	timer.reset();
}

void MagicCircleRenderer::render()
{
	float y = transform.getPos().y;
	shader->bind();
	if (timer.getEllapsedMicroSeconds() < 15.f / 100.f * time) {
		float factor = timer.getEllapsedMicroSeconds() / (15.f / 100.f * time) * size;
		transform.setScale(factor, factor, 1.f);
	}

	if (timer.getEllapsedMicroSeconds() > 85.f / 100.f * time) {
		float factor = size - ((time - timer.getEllapsedMicroSeconds()) / (15.f / 100.f * time) * size);
		transform.setScale(factor, factor, 1.f);
	}

	for (int i = 0; i < textures.size(); i++) {
		transform.addPos(0, 0.5, 0);
		shader->setMatrix4f("transform", transform.computeMatrix());
		glBindVertexArray(this->VAOS[i]);
		glDrawArrays(GL_QUADS, 0, 4);
	}
	transform.setPos(transform.getPos().x, y, transform.getPos().z);
	glBindVertexArray(0);
}
