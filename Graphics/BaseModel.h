#pragma once
#include "BaseHeader.h"
#include "Vectors.h"

class BaseModel
{
	virtual void draw(
		ShaderProgram& shader,
		Camera& camera,
		graphics::vec3 translation,
		graphics::vec4 rotation,
		graphics::vec3 scale
	) = 0;
};