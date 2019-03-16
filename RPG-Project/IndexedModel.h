#ifndef INDEXED_MODEL_H
#define INDEXED_MODEL_H

#include <vector>
#include <GL/glew.h>

class IndexedModel
{
public:
	IndexedModel(unsigned int facesCount);
	virtual ~IndexedModel();

	void clear();

	GLuint *m_pos;
	GLuint *m_col;
	GLuint *m_norm;
	GLuint *m_indices;
	unsigned int indices_count;
	unsigned int total_pos;
	unsigned int total_col;
	unsigned int total_norm;
	unsigned int total_id;
};
#endif
