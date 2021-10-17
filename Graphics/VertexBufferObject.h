#pragma once
#include <glad/glad.h>

class VertexBufferObject
{
	GLuint id;
public:
	VertexBufferObject(GLfloat* vertices, GLsizeiptr size, GLenum usagetype);
	~VertexBufferObject();
	void bind();
	void unbind();
};