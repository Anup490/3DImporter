#pragma once
#include <glm/glm.hpp>
#include "BaseHeader.h"
#include <memory>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBOCore;

class VertexBufferObject
{
	std::shared_ptr<VBOCore> pcore;
public:
	VertexBufferObject(Vertex* vertices, GLsizeiptr size, GLenum usagetype);
	VertexBufferObject(const VertexBufferObject& another_VBO);
	void bind();
	void unbind();
	VertexBufferObject& operator=(const VertexBufferObject& another_VBO);
};