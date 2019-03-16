#include "pch.h"
#include "Camera.h"
#include <iostream>


Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
	yaw = 0;
	pitch = 0;
	matrix_view = glm::perspective(fov, aspect, zNear, zFar);
	pos = glm::vec3();
	forward = glm::vec3(0.f, 0.f, 1.f);
	left = glm::vec3(0.f, 0.f, 1.f);
	up = glm::vec3(0.f, 1.f, 0.f);
	updateLook();
}

Camera::~Camera()
{
}

glm::vec3 Camera::getPos()
{
	return this->pos;
}

void Camera::setPos(float x, float y, float z)
{
	pos.x = x;
	pos.y = y;
	pos.z = z;
}

void Camera::addPos(float x, float y, float z)
{
	pos.x += x;
	pos.y += y;
	pos.z += z;
}

void Camera::setYaw(float yaw)
{
	this->yaw = yaw;
}

void Camera::setPitch(float pitch)
{
	if (pitch > 89.99)
		pitch = 89.99;
	if (pitch < -89.99)
		pitch = -89.99;
	this->pitch = pitch;
}

void Camera::setRot(float yaw, float pitch)
{
	this->setYaw(yaw);
	this->setPitch(pitch);
	updateLook();
}

void Camera::addRot(float yaw, float pitch)
{
	this->setYaw(this->getYaw() + yaw);
	this->setPitch(this->getPitch() + pitch);
	updateLook();
}

glm::mat4 Camera::getProjectionMatrix()
{
	return matrix_view * glm::lookAt(pos, pos + forward, up);
}

void Camera::updateLook()
{
	forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward.y = sin(glm::radians(pitch));
	forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	forward = glm::normalize(forward);

	left.x = cos(glm::radians(yaw - 90)) * cos(glm::radians(pitch));
	left.y = sin(glm::radians(pitch));
	left.z = sin(glm::radians(yaw - 90)) * cos(glm::radians(pitch));
	left = glm::normalize(left);
}