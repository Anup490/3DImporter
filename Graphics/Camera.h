#pragma once
#include "BaseCamera.h"
#include <glm/glm.hpp>

class Window;
class ShaderProgram;

class Camera : public BaseCamera
{
	glm::vec3 position, up, normal;
	Window* pwindow;
	float last_frame = 0.0f, yaw = -90.0f, pitch = 0.0f, lastX = 0.0f, lastY = 0.0f, fov = 45.0f, aspect_ratio = 1.0f;
	glm::vec3 front = glm::vec3(0.0f, 0.0f, 0.0f);
	bool first_mouse = true;
	glm::vec3 get_orientation();
	float get_delta_time();
public:
	Camera(Window& window, glm::vec3& position, glm::vec3& up);
	void set_model_matrix(ShaderProgram& program, glm::vec3& item_pos, glm::vec3 rotate_axis, float rotate_angle = 0.0f, glm::vec3 scalar = glm::vec3(1.0f));
	void set_view_matrix(ShaderProgram& program, bool keep_translation = true);
	void set_projection_matrix(ShaderProgram& program, float aspect_ratio = 1.0f, float fov = 45.0f);
	void update_position();
	void update_matrices(ShaderProgram& program);
	void on_mouse_move(GLFWwindow* window, double xpos, double ypos) override;
	void on_scroll(GLFWwindow* window, double xpos, double ypos) override;
	glm::vec3 get_position();
	glm::vec3 get_front();
};

