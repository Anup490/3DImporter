#pragma once
#include "BaseHeader.h"
#include <string>
#include <memory>

class TextureCore;

class Texture
{
	std::shared_ptr<TextureCore> pcore;
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
	Texture(const Texture& another_texture);
	void activate();
	void deactivate();
	const char* get_uniform();
	Texture& operator=(Texture& another_texture);
};