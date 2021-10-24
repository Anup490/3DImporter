#include "pch.h"
#include "Window.h"
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

Window::Window(const char* title, int width, int height)
{
	initialize_glfw(title, width, height);
	initialize_glad(width, height);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Window::should_stay()
{
	return !glfwWindowShouldClose(window);
}

void Window::run_swapbuffer_eventpoller()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

double Window::get_current_time()
{
	return glfwGetTime();
}

bool Window::has_pressed(int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}

void Window::activate_mouse_input(function mouse_callback, function scroll_callback)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
}

void Window::initialize_glfw(const char* title, int width, int height)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error loading window for " << title << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);
}

void Window::initialize_glad(int width, int height)
{
	gladLoadGL();
	glViewport(0, 0, width, height);
}

void Window::clear_color_buffer(glm::vec4& color, Enum bits)
{
	glClearColor(color.r,color.g,color.b,color.a);
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