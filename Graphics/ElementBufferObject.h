#pragma once
#include "BaseHeader.h"
#include <memory>

class EBOCore;

class ElementBufferObject
{
	std::shared_ptr<EBOCore> pcore;
public:
	ElementBufferObject(GLuint* indices, GLsizeiptr size, GLenum usage);
	ElementBufferObject(const ElementBufferObject& another_EBO);
	void bind();
	void unbind();
	ElementBufferObject& operator=(const ElementBufferObject& another_EBO);
};