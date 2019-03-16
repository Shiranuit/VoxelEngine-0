#include "pch.h"
#include "IndexedModel.h"


IndexedModel::IndexedModel(unsigned int facesCount)
{
	indices_count = 0;
	total_col = 0;
	total_pos = 0;
	total_id = 0;
	m_pos = (GLuint *)malloc(sizeof(GLuint) * (facesCount * 4));
	m_col = (GLuint *)malloc(sizeof(GLuint) * (facesCount * 4));
	m_indices = (GLuint *)malloc(sizeof(GLuint) * (facesCount * 6));
}

IndexedModel::~IndexedModel()
{
	delete m_pos;
	delete m_col;
	delete m_indices;
}


void IndexedModel::clear() {

	total_col = 0;
	total_pos = 0;
	total_id = 0;

	indices_count = 0;
}