#include "pch.h"
#include <stb/stb_image.h>
#include <string>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include "Cubemap.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "ShaderProgram.h"

Cubemap::Cubemap(std::vector<std::string>& paths)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
	load_cubemaps(paths);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	std::vector<Vertex> vertices = get_vertices();
	VertexBufferObject VBO(vertices.data(), vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
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

std::vector<Vertex> Cubemap::get_vertices()
{
	return std::vector<Vertex> {
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},

		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},

		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},

		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},

		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},

		Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f,  1.0f)}
	};
}