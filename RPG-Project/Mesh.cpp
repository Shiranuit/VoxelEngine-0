#include "pch.h"
#include "Mesh.h"

Mesh::Mesh()
{
}

void Mesh::initModel(IndexedModel &model)
{
	numVertices = model.total_id;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(NUM_BUFFERS, BUFFERS);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, BUFFERS[POSITION_VERTEXBUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.m_pos[0]) * model.total_pos, &model.m_pos[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribIPointer(0, 1, GL_UNSIGNED_INT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, BUFFERS[COLOR_VERTEXBUFFER]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.m_col[0]) * model.total_col, &model.m_col[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BUFFERS[INDICES_VERTEXBUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.m_indices[0]) * model.total_id, &model.m_indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


Mesh::~Mesh()
{
	glBindVertexArray(0);
	glDeleteBuffers(NUM_BUFFERS, BUFFERS);
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::render()
{
	glBindVertexArray(VAO);
	glDrawElementsBaseVertex(GL_TRIANGLES, numVertices, GL_UNSIGNED_INT, 0, 0);
	glBindVertexArray(0);
}