#pragma once
#include <glm/glm.hpp>
#include "BaseHeader.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VertexBufferObject
{
	GLuint id;
public:
	VertexBufferObject(std::vector<Vertex>& vertices, GLenum usagetype);
	~VertexBufferObject();
	void bind();
	void unbind();
};