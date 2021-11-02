#pragma once
#include "BaseHeader.h"
#include "Vectors.h"
#include "Matrix.h"

class Mesh
{
public:
	std::vector<Vertex>* pvertices;
	std::vector<GLuint>* pindices;
	std::vector<Texture*>* ptextures;
	VertexArrayObject* pVAO;
	VertexBufferObject* pVBO;
	ElementBufferObject* pEBO;
	Mesh
	(
		std::vector<Vertex>* pvertices,
		std::vector<GLuint>* pindices,
		std::vector<Texture*>* ptextures
	);
	Mesh(const Mesh& another_mesh);
	~Mesh();
	void draw
	(
		ShaderProgram& shader,
		Camera& camera,
		graphics::mat4 matrix = graphics::mat4(1.0f),
		graphics::vec3 translation = graphics::vec3(0.0f, 0.0f, 0.0f),
		graphics::vec4 rotation = graphics::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		graphics::vec3 scale = graphics::vec3(1.0f, 1.0f, 1.0f)
	);
	Mesh& operator=(const Mesh& another_mesh);
};