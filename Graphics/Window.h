#pragma once
#include <glad/glad.h>

class GLFWwindow;
class Window
{
	using function = void(GLFWwindow* window, double xpos, double ypos);

	GLFWwindow* window;
	void initialize_glfw(const char* title, int width, int height);
	void initialize_glad(int width, int height);
public:
	Window(const char* title, int width, int height);
	~Window();
	bool should_stay();
	void run_swapbuffer_eventpoller();
	double get_current_time();
	bool has_pressed(int key);
	void activate_mouse_input(function mouse_callback, function scroll_callback);
	void clear_color_buffer(float r, float g, float b, float a);
	void enable_depth_mask(GLboolean flag);
};