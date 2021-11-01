#include "pch.h"
#include "ShaderProgram.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <string>
#include <glad/glad.h>
#include "Utils.h"

ShaderProgram::ShaderProgram(const char* vertex_shader_path, const char* fragment_shader_path)
{
	id = glCreateProgram();
	std::string vertex_string = extract_shader(vertex_shader_path);
	std::string fragment_string = extract_shader(fragment_shader_path);
	const char* vertex_shader_source = vertex_string.c_str();
	const char* fragment_shader_source = fragment_string.c_str();
	GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	compile_shader(vertex_shader, vertex_shader_source, "vertex shader");
	GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	compile_shader(fragment_shader, fragment_shader_source, "fragment shader");
	link_shaders(vertex_shader, fragment_shader);
	delete_shaders(vertex_shader, fragment_shader);
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}

void ShaderProgram::activate()
{
	glUseProgram(id);
}

void ShaderProgram::deactivate()
{
	glUseProgram(0);
}

void ShaderProgram::set_float_uniform(const char* name, float value)
{
	activate();
	glUniform1f(glGetUniformLocation(id, name), value);
}

void ShaderProgram::set_int_uniform(const char* name, int value)
{
	activate();
	glUniform1i(glGetUniformLocation(id, name), value);
}

void ShaderProgram::set_mat4_uniform(const char* name, mat::mat4 value)
{
	activate();
	glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, glm::value_ptr(to_glm_mat4(value)));
}

void ShaderProgram::set_vec3_uniform(const char* name, vect::vec3 value)
{
	activate();
	glUniform3fv(glGetUniformLocation(id, name), 1, glm::value_ptr(to_glm_vec3(value)));
}

GLuint ShaderProgram::get_id()
{
	return id;
}

std::string ShaderProgram::extract_shader(const char* path)
{
	std::string shader_source = "";
	std::ifstream file_input_stream;
	std::stringstream string_stream;
	try
	{
		file_input_stream.open(path);
		string_stream << file_input_stream.rdbuf();
		file_input_stream.close();
		shader_source = string_stream.str();
	}
	catch (const std::ifstream::failure& f)
	{
		std::cout << "Failure reading :: " << path << std::endl;
		std::cout << "Error :: " << f.what() << std::endl;
	}
	return shader_source;
}

void ShaderProgram::compile_shader(GLuint shader_id, const char* shader_source, const char* shader_name)
{
	glShaderSource(shader_id, 1, &shader_source, NULL);
	glCompileShader(shader_id);
	int has_compiled;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &has_compiled);
	if (!has_compiled)
	{
		std::cout << "Error compiling " << shader_name << std::endl;
	}
}

template<typename... GLuints>
void ShaderProgram::link_shaders(GLuint shader_id, GLuints... shader_ids)
{
	glAttachShader(id, shader_id);
	link_shaders(shader_ids...);
}

void ShaderProgram::link_shaders()
{
	glLinkProgram(id);
	glCompileShader(id);
	int has_compiled;
	glGetShaderiv(id, GL_COMPILE_STATUS, &has_compiled);
	if (!has_compiled)
	{
		std::cout << "Error linking shaders " << std::endl;
	}
}

template<typename... GLuints>
void ShaderProgram::delete_shaders(GLuint shader_id, GLuints... shader_ids)
{
	glDeleteShader(shader_id);
	delete_shaders(shader_ids...);
}