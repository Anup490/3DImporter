#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
	GLuint id;
	GLenum texture_container;
	std::string uniform;
	void load_texture(const char* path);
	GLenum get_channel(int color_channel);
public:
	Texture
	(
		char const* path,
		char const* uniform,
		GLenum texture_container,
		GLint texture_wrap_s,
		GLint texture_wrap_t,
		GLint min_filter,
		GLint mag_filter
	);
	~Texture();
	void activate();
	void deactivate();
	const char* get_uniform();
};