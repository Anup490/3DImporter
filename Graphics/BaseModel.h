#pragma once
#include "BaseHeader.h"

class BaseModel
{
	virtual void draw(
		ShaderProgram& shader,
		Camera& camera,
		glm::vec3 translation,
		glm::quat rotation,
		glm::vec3 scale
	) = 0;
};