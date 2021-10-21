#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/vector_angle.hpp>

class ShaderProgram;
class Camera;

class BaseModel
{
	virtual void draw(
		ShaderProgram& shader,
		Camera& camera,
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	) = 0;
};