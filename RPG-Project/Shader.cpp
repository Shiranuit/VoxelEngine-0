#include "pch.h"
#include "Shader.h"

static GLuint createShader(std::string text, GLenum shaderType);
static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string error);

Shader::Shader(std::string fragmentShader, std::string vertexShader)
{
	FileReader fileFragmentShader(fragmentShader);
	FileReader fileVertexShader(vertexShader);
	program = glCreateProgram();
	
	if (!fileFragmentShader.isOpen())
		std::cerr << "ShaderError: Could not find fragmentShader '" << fragmentShader << "'" << std::endl;
	if (!fileVertexShader.isOpen())
		std::cerr << "ShaderError: Could not find vertexShader '" << vertexShader << "'" << std::endl;
	if (fileFragmentShader.isOpen() || fileVertexShader.isOpen()) {
		fShader = createShader(fileFragmentShader.readAll(), GL_FRAGMENT_SHADER);
		vShader = createShader(fileVertexShader.readAll(), GL_VERTEX_SHADER);

		glAttachShader(program, fShader);
		glAttachShader(program, vShader);

		glLinkProgram(program);
		checkShaderError(program, GL_LINK_STATUS, true, "ShaderError::Program:: Linking failed");
		
		glValidateProgram(program);
		checkShaderError(program, GL_VALIDATE_STATUS, true, "ShaderError::Program:: not a valid shader");

	}
}

static GLuint createShader(std::string text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);
	
	const GLchar* shaderSource[1];
	GLint shaderSourceLength[1];

	shaderSource[0] = text.c_str();
	shaderSourceLength[0] = (GLint)text.length();

	if (shader == 0)
		std::cerr << "ShaderError: Could not create a new Shader" << std::endl;
	else {
		glShaderSource(shader, 1, shaderSource, shaderSourceLength);
		glCompileShader(shader);
		if (shaderType == GL_FRAGMENT_SHADER)
			checkShaderError(shader, GL_COMPILE_STATUS, false, "ShaderError::FragmentShader::Compilation failed:: ");
		if (shaderType == GL_VERTEX_SHADER)
			checkShaderError(shader, GL_COMPILE_STATUS, false, "ShaderError::VertexShader::Compilation failed::");
	}
	return shader;
}

static void checkShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string error)
{
	GLint success = 0;
	GLchar err[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE) {
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(err), NULL, err);
		else
			glGetShaderInfoLog(shader, sizeof(err), NULL, err);
		std::cerr << error << "\n" << err << std::endl;
	}
}

Shader::~Shader()
{
	glDetachShader(program, fShader);
	glDeleteShader(fShader);
	
	glDetachShader(program, vShader);
	glDeleteShader(vShader);

	glDeleteProgram(program);
}

void Shader::bind() const
{
	glUseProgram(program);
}

void Shader::setBool(std::string name, bool val) const
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), (int)val);
}

void Shader::setInt(std::string name, int val) const
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), val);
}

void Shader::setFloat(std::string name, float val) const
{
	glUniform1f(glGetUniformLocation(program, name.c_str()), val);
}

void Shader::setVec3f(std::string name, float vals[3]) const
{
	glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &vals[0]);
}

void Shader::setVec3f(std::string name, glm::vec3 vec3) const
{
	glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, &vec3[0]);
}

void Shader::setMatrix4f(std::string name, glm::mat4 matrix4f) const
{
	glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &matrix4f[0][0]);
}

void Shader::setLight(std::string name, Light *light)
{
	setInt(name + ".type", light->type);

	setVec3f(name + ".position", light->position);
	setVec3f(name + ".direction", light->direction);

	setVec3f(name + ".ambient", light->ambient);
	setVec3f(name + ".diffuse", light->diffuse);
	setVec3f(name + ".specular", light->specular);
	
	setFloat(name + ".constant", light->constant);
	setFloat(name + ".linear", light->linear);
	setFloat(name + ".quadratic", light->quadratic);

	setFloat(name + ".ambientIntensity", light->ambientIntensity);
	setFloat(name + ".diffuseIntensity", light->diffuseIntensity);
	setFloat(name + ".specularIntensity", light->specularIntensity);

	setFloat(name + ".cutOff", light->cutOff);
	setFloat(name + ".outerCutOff", light->outerCutOff);
}