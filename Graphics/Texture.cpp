#include "pch.h"
#include "Texture.h"
#include "stb/stb_image.h"
#include <iostream>

class TextureCore
{
	GLuint id;
	GLenum texture_container;
public:
	TextureCore
	(
		GLenum texture_container,
		GLint texture_wrap_s,
		GLint texture_wrap_t,
		GLint min_filter,
		GLint mag_filter
	)
	{
		TextureCore::texture_container = texture_container;
		glGenTextures(1, &id);
		glActiveTexture(texture_container);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_wrap_s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_wrap_t);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
	}

	~TextureCore()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glDeleteTextures(1, &id);
	}

	void set_texture(int width, int height, GLenum color_channel, unsigned char* data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, color_channel, GL_UNSIGNED_BYTE, data);
	}

	void bind()
	{
		glActiveTexture(texture_container);
		glBindTexture(GL_TEXTURE_2D, id);
	}

	void unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};


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
	Texture::uniform = uniform;
	pcore = std::shared_ptr<TextureCore>(new TextureCore(texture_container, texture_wrap_s, texture_wrap_t, min_filter, mag_filter));
	load_texture(path);
	pcore->unbind();
}

Texture::Texture(const Texture& another_texture)
{
	this->pcore = another_texture.pcore;
	this->uniform = another_texture.uniform;
}

void Texture::activate()
{
	pcore->bind();
}

void Texture::deactivate()
{
	pcore->unbind();
}

Texture& Texture::operator=(Texture& another_texture)
{
	this->pcore = another_texture.pcore;
	this->uniform = another_texture.uniform;
	return *this;
}

void Texture::load_texture(const char* path)
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, color_channels;
	unsigned char* data = stbi_load(path, &width, &height, &color_channels, 0);
	if (data)
	{
		pcore->set_texture(width, height, get_channel(color_channels), data);
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