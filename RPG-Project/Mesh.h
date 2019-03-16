#ifndef MESH_H
#define MESH_H

#define NUM_BUFFERS 3

#include <GL/glew.h>
#include "IndexedModel.h"

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();
	void initModel(IndexedModel &model);
	void render();

private:
	GLuint VAO;
	GLuint BUFFERS[NUM_BUFFERS];
	unsigned int numVertices;
	enum
	{
		POSITION_VERTEXBUFFER,
		COLOR_VERTEXBUFFER,
		INDICES_VERTEXBUFFER,
	};
};

#endif