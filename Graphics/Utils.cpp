#include "pch.h"
#include "Utils.h"

glm::vec2 to_glm_vec2(graphics::vec2 vec)
{
	return glm::vec2(vec.x, vec.y);
}

graphics::vec2 to_vect_vec2(glm::vec2 vec)
{
	return graphics::vec2(vec.x, vec.y);
}

glm::vec3 to_glm_vec3(graphics::vec3 vec)
{
	return glm::vec3(vec.x, vec.y, vec.z);
}

graphics::vec3 to_vect_vec3(glm::vec3 vec)
{
	return graphics::vec3(vec.x, vec.y, vec.z);
}

glm::mat4 to_glm_mat4(graphics::mat4 mat)
{
	glm::mat4 glmmat(1.0f);
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			glmmat[c][r] = mat.m[r][c];
		}
	}
	return glmmat;
}

graphics::mat4 to_mat_mat4(glm::mat4 glmmat)
{
	graphics::mat4 mat(1.0f);
	for (int c = 0; c < 4; c++)
	{
		for (int r = 0; r < 4; r++)
		{
			mat.m[r][c] = glmmat[c][r];
		}
	}
	return mat;
}

glm::quat to_glm_quat(graphics::vec4 vec)
{
	return glm::quat(vec.w, vec.x, vec.y, vec.z);
}

graphics::vec4 to_vect_vec4(glm::quat quat)
{
	return graphics::vec4(quat.w, quat.x, quat.y, quat.z);
}