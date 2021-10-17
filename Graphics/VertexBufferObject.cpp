#include "pch.h"
#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(GLfloat* vertices, GLsizeiptr size, UsageType usagetype)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, get_usage(usagetype));
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

GLenum VertexBufferObject::get_usage(UsageType type)
{
	switch (type)
	{
	case UsageType::STREAM:
		return GL_STREAM_DRAW;
	case UsageType::DYNAMIC:
		return GL_DYNAMIC_DRAW;
	default:
		return GL_STATIC_DRAW;
	}
}