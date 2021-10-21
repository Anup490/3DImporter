#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtx/vector_angle.hpp>
#include <vector>
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "Texture.h"

class ShaderProgram;
class Camera;
namespace std
{
	template <class _Ty>
	class allocator;
	template <class _Ty, class _Alloc = allocator<_Ty>>
	class vector;
}

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;
	VertexArrayObject VAO;
	Mesh
	(
		std::vector<Vertex>& vertices,
		std::vector<GLuint>& indices,
		std::vector<Texture>& textures
	);
	void draw
	(
		ShaderProgram& shader,
		Camera& camera,
		glm::mat4 matrix = glm::mat4(1.0f),
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);
};