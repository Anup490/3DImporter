#include "pch.h"
#include "Mesh.h"
#include <string>
#include "ElementBufferObject.h"
#include "Camera.h"
#include "ShaderProgram.h"


#include <iostream>
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
	VAO.bind();
	ElementBufferObject EBO(indices.data(), indices.size() * sizeof(GLuint), GL_STATIC_DRAW);
	EBO.bind();
	VertexBufferObject VBO(vertices, GL_STATIC_DRAW);
	VAO.link_vbo(VBO, 0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	VAO.link_vbo(VBO, 1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	VAO.link_vbo(VBO, 2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	VAO.link_vbo(VBO, 3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(9 * sizeof(float)));
	VAO.unbind();
	VBO.unbind();
	EBO.unbind();
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
	VAO.bind();
	camera.update_matrices(shader);
	for (int i = 0; i < textures.size(); i++)
	{
		shader.set_int_uniform(textures.at(i).get_uniform(), i);
		textures.at(i).activate();
	}
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	for (int j = 0; j < textures.size(); j++)
	{
		textures.at(j).deactivate();
	}
	VAO.unbind();
	shader.deactivate();
}
