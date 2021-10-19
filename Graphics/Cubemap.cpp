#include "pch.h"
#include "Cubemap.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "ShaderProgram.h"
#include <stb/stb_image.h>
#include <vector>
#include <iostream>

Cubemap::Cubemap
(
	std::vector<std::string>& paths,
	std::vector<Vertex>& vertices,
	GLint texture_wrap_s,
	GLint texture_wrap_t,
	GLint texture_wrap_r,
	GLint min_filter,
	GLint mag_filter
)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	load_cubemaps(paths);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, min_filter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, mag_filter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, texture_wrap_s);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, texture_wrap_t);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, texture_wrap_r);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	VertexBufferObject VBO(vertices, GL_STATIC_DRAW);
	pVAO = new VertexArrayObject;
	pVAO->link_vbo(VBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
}

Cubemap::~Cubemap()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &id);
	delete pVAO;
}

void Cubemap::draw(ShaderProgram& shader)
{
	pVAO->bind();
	shader.activate();
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	pVAO->unbind();
	shader.deactivate();
}

void Cubemap::load_cubemaps(std::vector<std::string>& paths)
{
	int width, height, nrChannels;
	for (unsigned int i = 0; i < paths.size(); i++)
	{
		unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, get_channel(nrChannels), GL_UNSIGNED_BYTE, data
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

GLenum Cubemap::get_channel(int color_channel)
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