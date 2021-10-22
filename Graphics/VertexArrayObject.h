#pragma once
#include "BaseHeader.h"

class VertexBufferObject;

class VertexArrayObject
{
	GLuint id;
public:
	VertexArrayObject();
	~VertexArrayObject();
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
};