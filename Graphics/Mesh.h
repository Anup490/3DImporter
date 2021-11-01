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
		mat::mat4 matrix = mat::mat4(1.0f),
		vect::vec3 translation = vect::vec3(0.0f, 0.0f, 0.0f),
		vect::vec4 rotation = vect::vec4(1.0f, 0.0f, 0.0f, 0.0f),
		vect::vec3 scale = vect::vec3(1.0f, 1.0f, 1.0f)
	);
	Mesh& operator=(const Mesh& another_mesh);
};