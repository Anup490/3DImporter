#pragma once
#include "BaseHeader.h"

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