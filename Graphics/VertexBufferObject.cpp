#include "pch.h"
#include "VertexBufferObject.h"
#include <glad/glad.h>

class VBOCore
{
	GLuint id;
public:
	VBOCore(Vertex* vertices, GLsizeiptr size, GLenum usagetype)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, usagetype);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	~VBOCore()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &id);
	}
	void bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}
	void unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
};

VertexBufferObject::VertexBufferObject(Vertex* vertices, GLsizeiptr size, GLenum usagetype)
{
	pcore = std::shared_ptr<VBOCore>(new VBOCore(vertices, size, usagetype));
}

VertexBufferObject::VertexBufferObject(const VertexBufferObject& another_VBO)
{
	pcore = another_VBO.pcore;
}

void VertexBufferObject::bind()
{
	pcore->bind();
}

void VertexBufferObject::unbind()
{
	pcore->unbind();
}

VertexBufferObject& VertexBufferObject::operator=(const VertexBufferObject& another_VBO)
{
	pcore = another_VBO.pcore;
	return *this;
}