//THIS FILE IS NOT MEANT TO BE USED OUTSIDE THE GRAPHICS PROJECT
#pragma once
#include "Vectors.h"
#include "Matrix.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

glm::vec2 to_glm_vec2(vect::vec2 vec);
vect::vec2 to_vect_vec2(glm::vec2 vec);
glm::vec3 to_glm_vec3(vect::vec3 vec);
vect::vec3 to_vect_vec3(glm::vec3 vec);
glm::mat4 to_glm_mat4(mat::mat4 mat);
mat::mat4 to_mat_mat4(glm::mat4 mat);
glm::quat to_glm_quat(vect::vec4 vec);
vect::vec4 to_vect_vec4(glm::quat quat);