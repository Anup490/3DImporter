#pragma once
#include <string>
#include <glad/glad.h>

namespace std
{
	template <class _Ty>
	class allocator;
	template <class _Ty, class _Alloc = allocator<_Ty>>
	class vector;
}

class Cubemap
{
	GLuint id;
	void load_cubemaps(std::vector<std::string>& paths, GLenum img_color_channels);
public:
	Cubemap
	(
		std::vector<std::string>& paths,
		GLint texture_wrap_s,
		GLint texture_wrap_t,
		GLint texture_wrap_r,
		GLint min_filter,
		GLint mag_filter,
		GLenum img_color_channels
	);
	~Cubemap();
	void bind();
	void unbind();
};