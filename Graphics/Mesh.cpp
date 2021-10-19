#include "pch.h"
#include "Mesh.h"
#include <string>
#include <vector>
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "ElementBufferObject.h"
#include "Camera.h"
#include "Texture.h"
#include "ShaderProgram.h"

Mesh::Mesh
(
	std::vector<Vertex>& vertices,
	std::vector<GLuint>& indices,
	std::vector<Texture>& textures
)
{
	pvertices = &vertices;
	pindices = &indices;
	ptextures = &textures;
	pVAO = new VertexArrayObject;
	pVAO->bind();
	ElementBufferObject EBO(indices.data(), indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
	EBO.bind();
	VertexBufferObject VBO(vertices, GL_STATIC_DRAW);
	pVAO->link_vbo(VBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	pVAO->link_vbo(VBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	pVAO->link_vbo(VBO, 2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	pVAO->link_vbo(VBO, 3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
	pVAO->unbind();
	VBO.unbind();
	EBO.unbind();
}

Mesh::~Mesh()
{
	delete pVAO;
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
	for (int i = 0; i < ptextures->size(); i++)
	{
		shader.set_int_uniform(ptextures->at(i).get_uniform(), i);
		ptextures->at(i).activate();
	}
	glDrawElements(GL_TRIANGLES, pindices->size(), GL_UNSIGNED_INT, 0);
	for (int i = 0; i < ptextures->size(); i++)
	{
		ptextures->at(i).deactivate();
	}
	pVAO->unbind();
	shader.deactivate();
}
