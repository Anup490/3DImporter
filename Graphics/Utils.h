//THIS FILE IS NOT MEANT TO BE USED OUTSIDE THE GRAPHICS PROJECT
#pragma once
#include "Vectors.h"
#include "Matrix.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

glm::vec2 to_glm_vec2(graphics::vec2 vec);
graphics::vec2 to_vect_vec2(glm::vec2 vec);
glm::vec3 to_glm_vec3(graphics::vec3 vec);
graphics::vec3 to_vect_vec3(glm::vec3 vec);
glm::mat4 to_glm_mat4(graphics::mat4 mat);
graphics::mat4 to_mat_mat4(glm::mat4 mat);
glm::quat to_glm_quat(graphics::vec4 vec);
graphics::vec4 to_vect_vec4(glm::quat quat);