#ifndef TRANSFORM_H
#define TRANSFORM_H
#define GLM_ENABLE_EXPERIMENTAL

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>

class Transform
{
public:
	Transform();
	virtual ~Transform();

	glm::mat4 computeMatrix();

	glm::vec3 &getPos();
	glm::vec3 &getRot();
	glm::vec3 &getScale();

	void setPos(float x, float y, float z);
	void setRot(float x, float y, float z);
	void setScale(float x, float y, float z);
	
	void addPos(float x, float y, float z);
	void addRot(float x, float y, float z);
	void addScale(float x, float y, float z);

protected:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
	glm::mat4 transform;

};
#endif

