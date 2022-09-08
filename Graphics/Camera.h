#pragma once
#include "BaseCamera.h"
#include "Vectors.h"
#include "Matrix.h"

class Window;
class ShaderProgram;
class ImGUI;

class Camera : public BaseCamera
{
	graphics::vec3 position, original_position, up, normal;
	graphics::vec2 imgui_min;
	graphics::vec2 imgui_max;
	Window* pwindow;
	float last_frame = 0.0f, yaw = -90.0f, pitch = 0.0f, lastX = 0.0f, lastY = 0.0f, fov = 45.0f, aspect_ratio = 1.0f;
	graphics::vec3 front = graphics::vec3(0.0f, 0.0f, 0.0f);
	bool first_mouse = true, focus_imgui = false, enable_cam = true;
	void set_imgui_vectors(ImGUI& imgui);
	graphics::vec3 get_orientation();
	float get_delta_time();
	void handle_drag();
	bool should_drag();
	bool should_disable_imgui_focus(graphics::vec2& mouse_pos, graphics::vec2 window_dim);
public:
	Camera(Window& window, ImGUI& imgui, graphics::vec3& position, graphics::vec3& up);
	void set_model_matrix(ShaderProgram& program, graphics::vec3& item_pos, graphics::vec3 rotate_axis, float rotate_angle = 0.0f, graphics::vec3 scalar = graphics::vec3(1.0f));
	void set_model_matrix(ShaderProgram& program, graphics::mat4 matrix);
	void set_view_matrix(ShaderProgram& program, bool keep_translation = true);
	void set_projection_matrix(ShaderProgram& program, float aspect_ratio = 1.0f, float fov = 45.0f);
	void update_position();
	void update_matrices(ShaderProgram& program);
	void update_matrices_for_cubemap(ShaderProgram& program);
	void on_mouse_move(GLFWwindow* window, double xpos, double ypos) override;
	void on_scroll(GLFWwindow* window, double xpos, double ypos) override;
	void enable(bool enable);
	graphics::vec3 get_position();
	graphics::vec3 get_front();
	void reset();
};

