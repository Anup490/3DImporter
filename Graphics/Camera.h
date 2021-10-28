#pragma once
#include "BaseCamera.h"
#include "Vectors.h"

class Window;
class ShaderProgram;

class Camera : public BaseCamera
{
	vect::vec3 position, up, normal;
	Window* pwindow;
	float last_frame = 0.0f, yaw = -90.0f, pitch = 0.0f, lastX = 0.0f, lastY = 0.0f, fov = 45.0f, aspect_ratio = 1.0f;
	vect::vec3 front = vect::vec3(0.0f, 0.0f, 0.0f);
	bool first_mouse = true;
	vect::vec3 get_orientation();
	float get_delta_time();
	void handle_drag();
public:
	Camera(Window& window, vect::vec3& position, vect::vec3& up);
	void set_model_matrix(ShaderProgram& program, vect::vec3& item_pos, vect::vec3 rotate_axis, float rotate_angle = 0.0f, vect::vec3 scalar = vect::vec3(1.0f));
	void set_view_matrix(ShaderProgram& program, bool keep_translation = true);
	void set_projection_matrix(ShaderProgram& program, float aspect_ratio = 1.0f, float fov = 45.0f);
	void update_position();
	void update_matrices(ShaderProgram& program);
	void on_mouse_move(GLFWwindow* window, double xpos, double ypos) override;
	void on_scroll(GLFWwindow* window, double xpos, double ypos) override;
	vect::vec3 get_position();
	vect::vec3 get_front();
};

