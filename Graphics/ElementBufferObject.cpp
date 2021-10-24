#include "pch.h"
#include "ElementBufferObject.h"
#include <glad/glad.h>

class EBOCore
{
	GLuint id;
public:
	EBOCore(GLuint* indices, GLsizeiptr size, GLenum usage)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	~EBOCore()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &id);
	}
	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}
	void unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
};

ElementBufferObject::ElementBufferObject(GLuint* indices, GLsizeiptr size, GLenum usage)
{
	pcore = std::shared_ptr<EBOCore>(new EBOCore(indices, size, usage));
}

ElementBufferObject::ElementBufferObject(const ElementBufferObject& another_EBO)
{
	pcore = another_EBO.pcore;
}

void ElementBufferObject::bind()
{
	pcore->bind();
}

void ElementBufferObject::unbind()
{
	pcore->unbind();
}

ElementBufferObject& ElementBufferObject::operator=(const ElementBufferObject& another_EBO)
{
	pcore = another_EBO.pcore;
	return *this;
}