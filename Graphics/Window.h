#pragma once
#include "BaseHeader.h"
#include "Enum.h"
#include "Vectors.h"

struct GLFWwindow;
class Window
{
	using function = void(GLFWwindow* window, double xpos, double ypos);
	
	vect::vec2 dimensions;
	void initialize_glfw(const char* title, int width, int height);
	void initialize_glad(int width, int height);
public:
	GLFWwindow* pwindow;
	Window(const char* title, int width, int height);
	~Window();
	bool should_stay();
	void run_swapbuffer_eventpoller();
	double get_current_time() const;
	bool has_pressed_key(Enum key);
	bool has_pressed_mouse_btn(Enum btn);
	bool has_released_mouse_btn(Enum btn);
	void activate_mouse_input(function mouse_callback, function scroll_callback);
	void clear_color_buffer(vect::vec4& color, Enum bits);
	void enable_depth_mask(bool flag);
	void enable_feature(Enum cap);
	vect::vec2 get_dimensions() const;
	vect::vec2 get_mouse_cursor_pos() const;
	void set_mouse_cursor_pos(float x, float y);
	void show_mouse_cursor(bool show);
	GLFWwindow* get_window() const;
};