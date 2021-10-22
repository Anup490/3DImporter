#pragma once
#include "BaseHeader.h"

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
	void clear_color_buffer(glm::vec4& color, GLenum bits);
	void enable_depth_mask(GLboolean flag);
};