#pragma once
#include "BaseHeader.h"
#include <memory>

class VertexBufferObject;

class VAOCore;

class VertexArrayObject
{
	std::shared_ptr<VAOCore> pcore;
public:
	VertexArrayObject();
	VertexArrayObject(const VertexArrayObject& another_VAO);
	void link_vbo(
		VertexBufferObject& VBO, 
		GLuint index, 
		GLint size,
		GLenum type, 
		GLboolean normalized, 
		GLsizei stride, 
		const void* offset
	);
	void bind();
	void unbind();
	VertexArrayObject& operator=(const VertexArrayObject& another_VAO);
};