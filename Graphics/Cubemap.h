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
struct Vertex;
class VertexArrayObject;
class ShaderProgram;
class Cubemap
{
	GLuint id;
	VertexArrayObject* pVAO;
	void load_cubemaps(std::vector<std::string>& paths);
	GLenum get_channel(int color_channel);
public:
	Cubemap
	(
		std::vector<std::string>& paths,
		std::vector<Vertex>& vertices,
		GLint texture_wrap_s,
		GLint texture_wrap_t,
		GLint texture_wrap_r,
		GLint min_filter,
		GLint mag_filter
	);
	~Cubemap();
	void draw(ShaderProgram& shader);
};