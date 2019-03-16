#include "pch.h"
#include "Transform.h"


Transform::Transform()
{
	m_pos = glm::vec3();
	m_rot = glm::vec3();
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	transform = glm::mat4(1.0f);
}

Transform::~Transform()
{
}

glm::mat4 Transform::computeMatrix()
{
	glm::mat4 posM = glm::translate(m_pos);
	glm::mat4 rotZM = glm::rotate(m_rot.x, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 rotYM = glm::rotate(m_rot.y, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 rotXM = glm::rotate(m_rot.z, glm::vec3(0.0f, 0.0f, 1.0f));
	glm::mat4 scaleM = glm::scale(m_scale);

	glm::mat4 rotM = rotZM * rotYM * rotXM;
	transform = posM * rotM * scaleM;
	return transform;
}

glm::vec3 &Transform::getPos()
{
	return m_pos;
}

glm::vec3 &Transform::getRot()
{
	return m_rot;
}

glm::vec3 &Transform::getScale() {
	return m_scale;
}

void Transform::setPos(float x, float y, float z) {
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void Transform::setRot(float x, float y, float z) {
	m_rot.x = x;
	m_rot.y = y;
	m_rot.z = z;
}

void Transform::setScale(float x, float y, float z) {
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

void Transform::addPos(float x, float y, float z) {
	m_pos.x += x;
	m_pos.y += y;
	m_pos.z += z;
}

void Transform::addRot(float x, float y, float z) {
	m_rot.x += x;
	m_rot.y += y;
	m_rot.z += z;
}

void Transform::addScale(float x, float y, float z) {
	m_scale.x += x;
	m_scale.y += y;
	m_scale.z += z;
}