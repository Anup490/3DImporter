#pragma once
#include <glm/fwd.hpp>
#include <glad/glad.h>
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

namespace glm
{
	template<int a, typename T, qualifier Q>
	struct vec;
	template<typename T, qualifier Q>
	struct qua;
	template<int a, int b, typename T, qualifier Q>
	struct mat;
}

class GLFWwindow;
class Window;
class BaseCamera;
struct Vertex;
class VertexArrayObject;
class ShaderProgram;
class Camera;