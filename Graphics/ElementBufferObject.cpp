#include "pch.h"
#include "ElementBufferObject.h"

ElementBufferObject::ElementBufferObject(GLuint* indices, GLsizeiptr size, GLenum usage)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

ElementBufferObject::~ElementBufferObject()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &id);
}

void ElementBufferObject::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void ElementBufferObject::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}