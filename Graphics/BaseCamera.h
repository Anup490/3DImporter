#pragma once
struct GLFWwindow;

class BaseCamera
{
public:
	virtual void on_mouse_move(GLFWwindow* window, double xpos, double ypos) = 0;
	virtual void on_scroll(GLFWwindow* window, double xpos, double ypos) = 0;
};