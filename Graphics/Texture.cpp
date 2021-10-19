#include "pch.h"
#include "Texture.h"
#include "stb/stb_image.h"
#include <iostream>

Texture::Texture
(
	char const* path,
	char const* uniform,
	GLenum texture_container,
	GLint texture_wrap_s,
	GLint texture_wrap_t,
	GLint min_filter,
	GLint mag_filter
)
{
	glGenTextures(1, &id);
	glActiveTexture(texture_container);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	load_texture(path);
	Texture::texture_container = texture_container;
	Texture::uniform = uniform;
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	deactivate();
	glDeleteTextures(1, &id);
}

void Texture::activate()
{
	glActiveTexture(texture_container);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::deactivate()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load_texture(const char* path)
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, color_channels;
	unsigned char* data = stbi_load(path, &width, &height, &color_channels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, get_channel(color_channels), GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	else
	{
		std::cout << "Unable to load texture" << std::endl;
	}
}

const char* Texture::get_uniform()
{
	return uniform.c_str();
}

GLenum Texture::get_channel(int color_channel)
{
	switch (color_channel)
	{
	case 4:
		return GL_RGBA;
	case 3:
		return GL_RGB;
	default:
		return GL_RED;
	}
}