#pragma once
#include "BaseHeader.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

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
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
	Mesh& operator=(const Mesh& another_mesh);
};