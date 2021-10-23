#include "pch.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"

class VAOCore
{
public:
	GLuint id;
	VAOCore()
	{
		glGenVertexArrays(1, &id);
	}
	~VAOCore()
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &id);
	}
	void link_vbo(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
	{
		glBindVertexArray(id);
		glVertexAttribPointer(index, size, type, normalized, stride, offset);
		glEnableVertexAttribArray(index);
		glBindVertexArray(0);
	}
	void bind()
	{
		glBindVertexArray(id);
	}
	void unbind()
	{
		glBindVertexArray(0);
	}
};

VertexArrayObject::VertexArrayObject()
{
	pcore = std::shared_ptr<VAOCore>(new VAOCore);
}

VertexArrayObject::VertexArrayObject(const VertexArrayObject& another_VAO)
{
	pcore = another_VAO.pcore;
}

void VertexArrayObject::link_vbo(VertexBufferObject& VBO, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset)
{
	VBO.bind();
	pcore->link_vbo(index, size, type, normalized, stride, offset);
	VBO.unbind();
}

void VertexArrayObject::bind()
{
	pcore->bind();
}

void VertexArrayObject::unbind()
{
	pcore->unbind();
}

VertexArrayObject& VertexArrayObject::operator=(const VertexArrayObject& another_VAO)
{
	pcore = another_VAO.pcore;
	return *this;
}