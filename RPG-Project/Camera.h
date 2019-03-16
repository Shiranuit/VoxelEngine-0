#ifndef CAMERA_H
#define CAMERA_H
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
class Camera
{
public:
	Camera(float fov, float aspect, float zNear, float zFar);
	~Camera();
	void setPos(float x, float y, float z);
	void addPos(float x, float y, float z);
	void setRot(float pitch, float yaw);
	void addRot(float pitch, float yaw);
	float getYaw() { return this->yaw; };
	void setYaw(float yaw);
	float getPitch() { return this->pitch; };
	void setPitch(float pitch);
	glm::vec3 getPos();
	glm::vec3 getForward() { return this->forward; };
	glm::vec3 getLeft() { return this->left; };
	glm::mat4 getProjectionMatrix();
	void updateLook();

private:
	glm::mat4 matrix_view;
	glm::vec3 pos;
	glm::vec3 left;
	glm::vec3 forward;
	glm::vec3 up;
	float pitch;
	float yaw;
};
#endif
