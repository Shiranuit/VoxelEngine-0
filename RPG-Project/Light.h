#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

typedef struct Light {
	glm::vec3 position;
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	float ambientIntensity;
	float diffuseIntensity;
	float specularIntensity;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;

	unsigned int type;
};