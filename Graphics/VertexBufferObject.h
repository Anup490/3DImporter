#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace std
{
	template <class _Ty>
	class allocator;
	template <class _Ty, class _Alloc = allocator<_Ty>>
	class vector;
}

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VertexBufferObject
{
	GLuint id;
public:
	VertexBufferObject(std::vector<Vertex>& vertices, GLenum usagetype);
	~VertexBufferObject();
	void bind();
	void unbind();
};