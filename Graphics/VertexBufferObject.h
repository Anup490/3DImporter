#pragma once
#include <glad/glad.h>

enum class UsageType
{
	DYNAMIC, STATIC, STREAM
};

class VertexBufferObject
{
	GLuint id;
	GLenum get_usage(UsageType type);
public:
	VertexBufferObject(GLfloat* vertices, GLsizeiptr size, UsageType usagetype);
	~VertexBufferObject();
	void bind();
	void unbind();
};