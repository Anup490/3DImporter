#include "pch.h"
#include "Mesh.h"
#include <string>
#include "ElementBufferObject.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Camera.h"
#include "ShaderProgram.h"
#include <vector>
#include "Texture.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include "Utils.h"

Mesh::Mesh
(
	std::vector<Vertex>* pvertices,
	std::vector<GLuint>* pindices,
	std::vector<Texture*>* ptextures
)
{
	Mesh::pvertices = pvertices;
	Mesh::pindices = pindices;
	Mesh::ptextures = ptextures;
	pVAO = new VertexArrayObject;
	pVAO->bind();
	pEBO = new ElementBufferObject(pindices->data(), pindices->size() * sizeof(GLuint), GL_STATIC_DRAW);
	pEBO->bind();
	pVBO = new VertexBufferObject(pvertices->data(), pvertices->size() * sizeof(Vertex), GL_STATIC_DRAW);
	pVAO->link_vbo(*pVBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	pVAO->link_vbo(*pVBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	pVAO->link_vbo(*pVBO, 2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	pVAO->link_vbo(*pVBO, 3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
	pVAO->unbind();
	pVAO->unbind();
	pEBO->unbind();
}

Mesh::Mesh(const Mesh& another_mesh) 
{
	this->pVAO = new VertexArrayObject(*another_mesh.pVAO);
	this->pVBO = new VertexBufferObject(*another_mesh.pVBO);
	this->pEBO = new ElementBufferObject(*another_mesh.pEBO);
	this->pvertices = another_mesh.pvertices;
	this->pindices = another_mesh.pindices;
	this->ptextures = another_mesh.ptextures;
}

Mesh::~Mesh()
{
	delete pVAO;
	delete pEBO;
	delete pVBO;
}

void Mesh::draw
(
	ShaderProgram& shader,
	Camera& camera,
	graphics::mat4 matrix,
	graphics::vec3 translation,
	graphics::vec4 rotation,
	graphics::vec3 scale
)
{
	shader.activate();
	pVAO->bind();
	camera.update_matrices(shader);
	camera.set_model_matrix(shader, matrix);

	int final_pos = ptextures->size() - 1;
	for (int i = final_pos; i >= 0; i--)
	{
		shader.set_int_uniform(ptextures->at(i)->get_uniform(), i);
		ptextures->at(i)->activate();
	}
	glDrawElements(GL_TRIANGLES, pindices->size(), GL_UNSIGNED_INT, 0);
	for (int i = 0; i < ptextures->size(); i++)
	{
		ptextures->at(i)->deactivate();
	}
	pVAO->unbind();
	shader.deactivate();
}

Mesh& Mesh::operator=(const Mesh& another_mesh)
{
	this->pVAO = new VertexArrayObject(*another_mesh.pVAO);
	this->pVBO = new VertexBufferObject(*another_mesh.pVBO);
	this->pEBO = new ElementBufferObject(*another_mesh.pEBO);
	this->pvertices = another_mesh.pvertices;
	this->pindices = another_mesh.pindices;
	this->ptextures = another_mesh.ptextures;
	return *this;
}