#include "pch.h"
#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(GLfloat* vertices, GLsizeiptr size, GLenum usagetype)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, usagetype);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferObject::~VertexBufferObject()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &id);
}

void VertexBufferObject::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBufferObject::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}