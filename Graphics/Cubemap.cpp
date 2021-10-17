#include "pch.h"
#include "Cubemap.h"
#include <stb/stb_image.h>
#include <vector>
#include <iostream>

Cubemap::Cubemap
(
	std::vector<std::string>& paths,
	GLint texture_wrap_s,
	GLint texture_wrap_t,
	GLint texture_wrap_r,
	GLint min_filter,
	GLint mag_filter,
	GLenum img_color_channels
)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	load_cubemaps(paths, img_color_channels);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, texture_wrap_s);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, texture_wrap_t);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, texture_wrap_r);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

Cubemap::~Cubemap()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &id);
}

void Cubemap::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void Cubemap::unbind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Cubemap::load_cubemaps(std::vector<std::string>& paths, GLenum img_color_channels)
{
	int width, height, nrChannels;
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, img_color_channels, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << paths[i] << std::endl;
			stbi_image_free(data);
		}
	}
}