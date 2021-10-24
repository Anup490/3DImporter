#pragma once
#include "BaseHeader.h"
#include "Matrix.h"
#include "Vectors.h"

class ShaderProgram
{
	GLuint id;
	std::string extract_shader(const char* path);
	void compile_shader(GLuint shader_id, const char* shader_source, const char* shader_name);
	template<typename... GLuints> void link_shaders(GLuint shader_id, GLuints... shader_ids);
	void link_shaders();
	template<typename... GLuints> void delete_shaders(GLuint shader_id, GLuints... shader_ids);
	void delete_shaders() {};
public:
	ShaderProgram(const char* vertex_shader_path, const char* fragment_shader_path);
	~ShaderProgram();
	void activate();
	void deactivate();
	void set_float_uniform(const char* name, float value);
	void set_int_uniform(const char* name, int value);
	void set_mat4_uniform(const char* name, mat::mat4 value);
	void set_vec3_uniform(const char* name, vect::vec3 value);
	GLuint get_id();
};