#ifndef SHADER_H
#define SHADER_H

#include <iomanip>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "FileReader.h"
#include "Transform.h"
#include "Light.h"

class Shader
{
public:
	Shader(std::string fragmentShader, std::string vertexShader);
	virtual ~Shader();
	void bind() const;
	void setBool(std::string name, bool val) const;
	void setInt(std::string name, int val) const;
	void setFloat(std::string name, float val) const;
	void setVec3f(std::string name, float vals[3]) const;
	void setVec3f(std::string name, glm::vec3 vec3) const;
	void setMatrix4f(std::string name, glm::mat4 matrix4f) const;
	void setLight(std::string name, Light *light);

private:
	GLuint program;
	GLuint vShader;
	GLuint fShader;
};

#endif // !SHADER_H