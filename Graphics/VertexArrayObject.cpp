#include "pch.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &id);
}

VertexArrayObject::~VertexArrayObject()
{
	//glBindVertexArray(0);
	//glDeleteVertexArrays(1, &id);
}

void VertexArrayObject::link_vbo(VertexBufferObject& VBO, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
{
	glBindVertexArray(id);
	VBO.bind();
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
	glEnableVertexAttribArray(index);
	glBindVertexArray(0);
	VBO.unbind();
}

void VertexArrayObject::bind()
{
	glBindVertexArray(id);
}

void VertexArrayObject::unbind()
{
	glBindVertexArray(0);
}