#pragma once
#include "BaseHeader.h"

class ElementBufferObject
{
	GLuint id;
public:
	ElementBufferObject(GLuint* indices, GLsizeiptr size, GLenum usage);
	~ElementBufferObject();
	void bind();
	void unbind();
};