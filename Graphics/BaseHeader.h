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

	template <class _Ty1, class _Ty2>
	struct pair;

	template <class _Ty = void>
	struct less;

	template <class _Kty, class _Ty, class _Pr = less<_Kty>, class _Alloc = allocator<pair<const _Kty, _Ty>>>
	class map;

	using string = basic_string<char, char_traits<char>, allocator<char>>;
}

struct Vertex;

class GLFWwindow;
class Window;
class BaseCamera;
class VertexArrayObject;
class VertexBufferObject;
class ElementBufferObject;
class ShaderProgram;
class Camera;
class Texture;

typedef int GLint;
typedef int GLsizei;
typedef unsigned int GLuint;
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef signed long long int GLsizeiptr;