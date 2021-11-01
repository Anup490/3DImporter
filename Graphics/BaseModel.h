#pragma once
#include "BaseHeader.h"
#include "Vectors.h"

class BaseModel
{
	virtual void draw(
		ShaderProgram& shader,
		Camera& camera,
		vect::vec3 translation,
		vect::vec4 rotation,
		vect::vec3 scale
	) = 0;
};