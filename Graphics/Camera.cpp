#include "pch.h"
#include "Camera.h"
#include "Window.h"
#include "ShaderProgram.h"
#include <glfw/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(Window& window, glm::vec3& position, glm::vec3& target, glm::vec3& up)
{
	Camera::pwindow = &window;
	Camera::position = position;
	Camera::target = target;
	Camera::up = up;
	Camera::view = glm::mat4(1.0f);
	Camera::projection = glm::mat4(1.0f);
	Camera::normal = glm::normalize(up);
	Camera::front = glm::normalize(get_orientation());
}

void Camera::set_model_matrix(ShaderProgram& program, glm::vec3& item_pos, glm::vec3 rotate_axis, float rotate_angle, glm::vec3 scalar)
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, scalar);
	model = glm::translate(model, item_pos);
	model = glm::rotate(model, glm::radians(rotate_angle), rotate_axis);
	program.set_mat4_uniform("model", model);
}

void Camera::set_view_matrix(ShaderProgram& program, bool keep_translation)
{
	Camera::view = (keep_translation)?glm::lookAt(position, position + front, normal):glm::mat4(glm::mat3(glm::lookAt(position, position + front, normal)));
	program.set_mat4_uniform("view", Camera::view);
	program.deactivate();
}

void Camera::set_projection_matrix(ShaderProgram& program, float aspect_ratio, float fov)
{
	Camera::fov = fov;
	Camera::projection = glm::perspective(fov, aspect_ratio, 0.1f, 100.0f);
	program.set_mat4_uniform("projection", Camera::projection);
	program.deactivate();
}

void Camera::update_position()
{
	const float speed = 10.0f * get_delta_time();
	if (pwindow->has_pressed(GLFW_KEY_W))
		position += speed * glm::normalize(front);
	if (pwindow->has_pressed(GLFW_KEY_S))
		position -= speed * glm::normalize(front);
	if (pwindow->has_pressed(GLFW_KEY_A))
		position -= speed * glm::normalize(glm::cross(front, normal));
	if (pwindow->has_pressed(GLFW_KEY_D))
		position += speed * glm::normalize(glm::cross(front, normal));
}

void Camera::update_matrices(ShaderProgram& program)
{
	Camera::view = glm::lookAt(position, position + front, normal);
	program.set_mat4_uniform("view", view);
	Camera::projection = glm::perspective(glm::radians(fov), aspect_ratio, 0.1f, 100.0f);
	program.set_mat4_uniform("projection", projection);
}

void Camera::on_mouse_move(GLFWwindow* window, double xpos, double ypos)
{
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
	front = glm::normalize(get_orientation());
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

glm::vec3 Camera::get_position()
{
	return position;
}

glm::vec3 Camera::get_front()
{
	return front;
}

glm::vec3 Camera::get_orientation()
{
	glm::vec3 orientation;
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