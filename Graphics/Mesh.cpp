#include "pch.h"
#include "Mesh.h"
#include <string>
#include "ElementBufferObject.h"
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"
#include "Camera.h"
#include "ShaderProgram.h"

Mesh::Mesh
(
	std::vector<Vertex>& vertices,
	std::vector<GLuint>& indices,
	std::vector<Texture>& textures
)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;
	pVAO = new VertexArrayObject;
	pVAO->bind();
	pEBO = new ElementBufferObject(indices.data(), indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
	pEBO->bind();
	pVBO = new VertexBufferObject(vertices.data(), vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);
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
	this->vertices = another_mesh.vertices;
	this->indices = another_mesh.indices;
	this->textures = another_mesh.textures;
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
	glm::mat4 matrix,
	glm::vec3 translation,
	glm::quat rotation,
	glm::vec3 scale
)
{
	shader.activate();
	pVAO->bind();
	camera.update_matrices(shader);
	int final_pos = textures.size() - 1;
	for (int i = final_pos; i >= 0; i--)
	{
		shader.set_int_uniform(textures.at(i).get_uniform(), i);
		textures.at(i).activate();
	}
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	for (int i = 0; i < textures.size(); i++)
	{
		textures.at(i).deactivate();
	}
	pVAO->unbind();
	shader.deactivate();
}

Mesh& Mesh::operator=(Mesh& another_mesh)
{
	this->pVAO = new VertexArrayObject(*another_mesh.pVAO);
	this->pVBO = new VertexBufferObject(*another_mesh.pVBO);
	this->pEBO = new ElementBufferObject(*another_mesh.pEBO);
	this->vertices = another_mesh.vertices;
	this->indices = another_mesh.indices;
	this->textures = another_mesh.textures;
	return *this;
}
