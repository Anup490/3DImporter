#include "pch.h"
#include "Camera.h"
#include "Window.h"
#include "ShaderProgram.h"
#include "Utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

//#define MOUSE_MOVE
#define MOUSE_DRAG

#include <iostream>

Camera::Camera(Window& window, vect::vec3& position, vect::vec3& up)
{
	Camera::pwindow = &window;
	Camera::position = position;
	Camera::up = up;
	Camera::normal = to_vect_vec3(glm::normalize(glm::vec3(up.x, up.y, up.z)));
	Camera::front = to_vect_vec3(glm::normalize(to_glm_vec3(get_orientation())));
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

bool click_imgui = false;

void Camera::handle_drag()
{
#ifdef MOUSE_DRAG
	vect::vec2 mouse_pos = pwindow->get_mouse_cursor_pos();
	if (mouse_pos.x < 550.0f || mouse_pos.y > 400.0f)
	{
		click_imgui = false;
	}
	if (click_imgui)
	{
		return;
	}
	if (mouse_pos.x >=550 && mouse_pos.x <=800)
	{
		if (mouse_pos.y >= 0 && mouse_pos.y <=100)
		{
			click_imgui = true;
			return;
		}
		else 
		{
			goto mouse_block;
		}
	}
	else
	{
		goto mouse_block;
	}
	
	mouse_block:
		if (pwindow->has_pressed_mouse_btn(Enum::MOUSE_BTN_LEFT))
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
			mouse_pos = pwindow->get_mouse_cursor_pos();

			float sensitivity = 100.0f;
			float rotX = sensitivity * (float)(mouse_pos.y - (height / 2)) / height;
			float rotY = sensitivity * (float)(mouse_pos.x - (width / 2)) / width;
			glm::vec3 Orientation = to_glm_vec3(front);
			glm::vec3 Up = to_glm_vec3(up);
			glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));
			if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
			{
				Orientation = newOrientation;
			}
			Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);
			pwindow->set_mouse_cursor_pos((width / 2), (height / 2));
			front = to_vect_vec3(glm::normalize(Orientation));
		}
		else if (pwindow->has_released_mouse_btn(Enum::MOUSE_BTN_LEFT))
		{
			pwindow->show_mouse_cursor(true);
			first_mouse = true;
		}
#endif
}