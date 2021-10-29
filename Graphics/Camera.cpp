#include "pch.h"
#include "Camera.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "Utils.h"
#include "Im_GUI.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

//#define MOUSE_MOVE
#define MOUSE_DRAG

#include <iostream>

Camera::Camera(Window& window, ImGUI& imgui, vect::vec3& position, vect::vec3& up)
{
	Camera::pwindow = &window;
	Camera::position = position;
	Camera::original_position = position;
	Camera::up = up;
	Camera::normal = to_vect_vec3(glm::normalize(glm::vec3(up.x, up.y, up.z)));
	Camera::front = to_vect_vec3(glm::normalize(to_glm_vec3(get_orientation())));
	set_imgui_vectors(imgui);
}

void Camera::set_model_matrix(ShaderProgram& program, vect::vec3& item_pos, vect::vec3 rotate_axis, float rotate_angle, vect::vec3 scalar)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(scalar.x, scalar.y, scalar.z));
	model = glm::translate(model, glm::vec3(item_pos.x, item_pos.y, item_pos.z));
	model = glm::rotate(model, glm::radians(rotate_angle), glm::vec3(rotate_axis.x, rotate_axis.y, rotate_axis.z));
	program.set_mat4_uniform("model", to_mat_mat4(model));
}

void Camera::set_view_matrix(ShaderProgram& program, bool keep_translation)
{
	glm::vec3 glmposition = to_glm_vec3(position);
	glm::vec3 glmfront = to_glm_vec3(front);
	glm::vec3 glmnormal = to_glm_vec3(normal);
	glm::mat4 view = (keep_translation)?glm::lookAt(glmposition, glmposition + glmfront, glmnormal):glm::mat4(glm::mat3(glm::lookAt(glmposition, glmposition + glmfront, glmnormal)));
	program.set_mat4_uniform("view", to_mat_mat4(view));
	program.deactivate();
}

void Camera::set_projection_matrix(ShaderProgram& program, float aspect_ratio, float fov)
{
	Camera::fov = fov;
	glm::mat4 projection = glm::perspective(fov, aspect_ratio, 0.1f, 100.0f);
	program.set_mat4_uniform("projection", to_mat_mat4(projection));
	program.deactivate();
}

void Camera::update_position()
{
	const float speed = 10.0f * get_delta_time();
	glm::vec3 glmposition = to_glm_vec3(position);
	glm::vec3 glmfront = to_glm_vec3(front);
	glm::vec3 glmnormal = to_glm_vec3(normal);
	if (pwindow->has_pressed_key(Enum::KEY_W))
		glmposition += speed * glm::normalize(glmfront);
	if (pwindow->has_pressed_key(Enum::KEY_S))
		glmposition -= speed * glm::normalize(glmfront);
	if (pwindow->has_pressed_key(Enum::KEY_A))
		glmposition -= speed * glm::normalize(glm::cross(glmfront, glmnormal));
	if (pwindow->has_pressed_key(Enum::KEY_D))
		glmposition += speed * glm::normalize(glm::cross(glmfront, glmnormal));
	position = to_vect_vec3(glmposition);
	handle_drag();
}

void Camera::update_matrices(ShaderProgram& program)
{
	glm::vec3 glmposition = to_glm_vec3(position);
	glm::vec3 glmfront = to_glm_vec3(front);
	glm::vec3 glmnormal = to_glm_vec3(normal);
	glm::mat4 view = glm::lookAt(glmposition, glmposition + glmfront, glmnormal);
	program.set_mat4_uniform("view", to_mat_mat4(view));
	glm::mat4 projection = glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
	program.set_mat4_uniform("projection", to_mat_mat4(projection));
}

void Camera::on_mouse_move(GLFWwindow* window, double xpos, double ypos)
{
#ifdef MOUSE_MOVE
	if (first_mouse)
	{
		lastX = xpos;
		lastY = ypos;
		first_mouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.1;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	yaw += xoffset;
	pitch += yoffset;
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;
	front = to_vect_vec3(glm::normalize(to_glm_vec3(get_orientation())));
#endif
}

void Camera::on_scroll(GLFWwindow* window, double xpos, double ypos)
{
	fov -= (float)ypos;
	if (fov < 1.0f)
	{
		fov = 1.0f;
	}
	else if (fov > 45.0f)
	{
		fov = 45.0f;
	}
}

vect::vec3 Camera::get_position()
{
	return vect::vec3(position.x, position.y, position.z);
}

vect::vec3 Camera::get_front()
{
	return vect::vec3(front.x, front.y, front.z);
}

void Camera::reset()
{
	position = original_position;
	yaw = -90.0f;
	pitch = 0.0f;
	front = get_orientation();
}

void Camera::set_imgui_vectors(ImGUI& imgui)
{
	vect::vec2 position = imgui.get_position();
	vect::vec2 size = imgui.get_size();
	imgui_min = vect::vec2(position.x, position.y);
	imgui_max = vect::vec2(position.x + size.x, position.y + size.y);
}

vect::vec3 Camera::get_orientation()
{
	vect::vec3 orientation(1.0f);
	orientation.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	orientation.y = sin(glm::radians(pitch));
	orientation.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	return orientation;
}

float Camera::get_delta_time()
{
	float delta_time = 0.0f, current_frame = pwindow->get_current_time();
	delta_time = current_frame - last_frame;
	last_frame = current_frame;
	return delta_time;
}

void Camera::handle_drag()
{
#ifdef MOUSE_DRAG
	if (pwindow->has_pressed_mouse_btn(Enum::MOUSE_BTN_LEFT))
	{
		if (should_drag())
		{
			pwindow->show_mouse_cursor(false);
			vect::vec2 window_dimension = pwindow->get_dimensions();
			float width = window_dimension.x;
			float height = window_dimension.y;
			if (first_mouse)
			{
				pwindow->set_mouse_cursor_pos((width / 2), (height / 2));
				first_mouse = false;
			}
			vect::vec2 mouse_pos = pwindow->get_mouse_cursor_pos();
			float sensitivity = 100.0f;
			float pitch = sensitivity * (float)(mouse_pos.y - (height / 2)) / height;
			float yaw = sensitivity * (float)(mouse_pos.x - (width / 2)) / width;
			glm::vec3 glmfront = to_glm_vec3(front);
			glm::vec3 glmup = to_glm_vec3(up);
			glm::vec3 new_glmfront = glm::rotate(glmfront, glm::radians(-pitch), glm::normalize(glm::cross(glmfront, glmup)));
			if (abs(glm::angle(new_glmfront, glmup) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				glmfront = new_glmfront;
			}
			glmfront = glm::rotate(glmfront, glm::radians(-yaw), glmup);
			pwindow->set_mouse_cursor_pos((width / 2), (height / 2));
			front = to_vect_vec3(glm::normalize(glmfront));
		}
	}
	else if (pwindow->has_released_mouse_btn(Enum::MOUSE_BTN_LEFT))
	{
		pwindow->show_mouse_cursor(true);
		first_mouse = true;
	}
#endif
}

bool Camera::should_drag()
{
	vect::vec2 mouse_pos = pwindow->get_mouse_cursor_pos();
	vect::vec2 window_dim = pwindow->get_dimensions().y;
	if (should_disable_imgui_focus(mouse_pos, window_dim))
	{
		focus_imgui = false;
	}
	if (mouse_pos.x >= imgui_min.x && mouse_pos.x <= imgui_max.x && mouse_pos.y >= imgui_min.y && mouse_pos.y <= imgui_max.y)
	{
		focus_imgui = true;
	}
	return !focus_imgui;
}

bool Camera::should_disable_imgui_focus(vect::vec2& mouse_pos, vect::vec2 window_dim)
{
	bool disable = false;
	if (imgui_max.x >= window_dim.x)
	{
		disable = (mouse_pos.x < (imgui_min.x - 100.0f)) || (mouse_pos.x > imgui_max.x);
	}
	else
	{
		disable = (mouse_pos.x < imgui_min.x) || (mouse_pos.x > (imgui_max.x + 200.0f));
	}
	if (imgui_max.y >= window_dim.y)
	{
		disable = disable && ((mouse_pos.y < imgui_min.y) || (mouse_pos.y > (imgui_max.y + 100.0f)));		
	}
	else
	{
		disable = disable && ((mouse_pos.y < (imgui_min.y - 100.0f)) || (mouse_pos.y > imgui_max.y));	
	}
	return disable;
}