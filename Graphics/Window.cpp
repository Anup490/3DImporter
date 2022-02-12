#include "pch.h"
#include "Window.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "Utils.h"

Window::Window(const char* title, int width, int height)
{
	dimensions = graphics::vec2(width, height);
	initialize_glfw(title, width, height);
	initialize_glad(width, height);
}

Window::~Window()
{
	glfwDestroyWindow(pwindow);
	glfwTerminate();
}

bool Window::should_stay()
{
	return !glfwWindowShouldClose(pwindow);
}

void Window::run_swapbuffer_eventpoller()
{
	glfwSwapBuffers(pwindow);
	glfwPollEvents();
}

double Window::get_current_time() const
{
	return glfwGetTime();
}

bool Window::has_pressed_key(Enum key)
{
	return glfwGetKey(pwindow, key.val) == GLFW_PRESS;
}

bool Window::has_pressed_mouse_btn(Enum btn)
{
	return glfwGetMouseButton(pwindow, btn.val) == GLFW_PRESS;
}

bool Window::has_released_mouse_btn(Enum btn)
{
	return glfwGetMouseButton(pwindow, btn.val) == GLFW_RELEASE;
}

void Window::activate_mouse_input(function mouse_callback, function scroll_callback)
{
	glfwSetInputMode(pwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(pwindow, mouse_callback);
	glfwSetScrollCallback(pwindow, scroll_callback);
}

void Window::initialize_glfw(const char* title, int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	pwindow = glfwCreateWindow(width, height, title, NULL, NULL);
	if (pwindow == NULL)
	{
		std::cout << "Error loading window for " << title << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(pwindow);
}

void Window::initialize_glad(int width, int height)
{
	gladLoadGL();
	glViewport(0, 0, width, height);
}

void Window::clear_color_buffer(graphics::vec4& color, Enum bits)
{
	glClearColor(color.x,color.y,color.z,color.w);
	glClear(bits.val);
}

void Window::enable_depth_mask(bool flag)
{
	glDepthMask((flag)?GL_TRUE:GL_FALSE);
}

void Window::enable_feature(Enum cap)
{
	glEnable(cap.val);
}

void Window::enable_back_face_culling(bool flag)
{
	if (flag)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
	}
	else
	{
		glDisable(GL_CULL_FACE);
	}
}

graphics::vec2 Window::get_dimensions() const
{
	return dimensions;
}

graphics::vec2 Window::get_mouse_cursor_pos() const
{
	double mouseX;
	double mouseY;
	glfwGetCursorPos(pwindow, &mouseX, &mouseY);
	return graphics::vec2(mouseX, mouseY);
}

void Window::set_mouse_cursor_pos(float x, float y)
{
	glfwSetCursorPos(pwindow, x, y);
}

void Window::show_mouse_cursor(bool show)
{
	glfwSetInputMode(pwindow, GLFW_CURSOR, (show)?GLFW_CURSOR_NORMAL:GLFW_CURSOR_HIDDEN);
}

GLFWwindow* Window::get_window() const
{
	return pwindow;
}