#include "pch.h"
#include "Texture.h"
#include <GL/glew.h>
#include <iomanip>
#include <iostream>

Texture::Texture(const std::string &filepath)
{
	int width, height, channels;
	unsigned char *data = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "Failed to load file" << std::endl;
	}
	stbi_image_free(data);
}

Texture::Texture(const char *filepath)
{
	int width, height, channels;
	unsigned char *data = stbi_load(filepath, &width, &height, &channels, 0);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cerr << "Failed to load file" << std::endl;
	}
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture);
}
