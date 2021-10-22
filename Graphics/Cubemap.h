#pragma once

namespace std
{
	template <class _Ty>
	class allocator;
	template <class _Ty, class _Alloc = allocator<_Ty>>
	class vector;

	template <class _Elem>
	struct char_traits;
	template <class _Elem, class _Traits = char_traits<_Elem>, class _Alloc = allocator<_Elem>>
	class basic_string;

	using string = basic_string<char, char_traits<char>, allocator<char>>;
}
struct Vertex;
class VertexArrayObject;
class ShaderProgram;
typedef unsigned int GLuint;

class Cubemap
{
	GLuint id;
	VertexArrayObject* pVAO;
	void load_cubemaps(std::vector<std::string>& paths);
	GLenum get_channel(int color_channel);
	std::vector<Vertex> get_vertices();
public:
	Cubemap(std::vector<std::string>& paths);
	~Cubemap();
	void draw(ShaderProgram& shader);
};