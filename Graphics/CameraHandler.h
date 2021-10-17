#pragma once

class GLFWwindow;
class Window;
class BaseCamera;
namespace std
{
	template <class _Ty>
	class allocator;
	template <class _Ty, class _Alloc = allocator<_Ty>>
	class vector;
}

class CameraHandler
{
	static std::vector<BaseCamera*>* pcameras;
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void scroll_callback(GLFWwindow* window, double xpos, double ypos);
public:
	CameraHandler(Window& window);
	~CameraHandler();
	void add_camera(BaseCamera* camera);
};