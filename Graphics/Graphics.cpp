#include "pch.h"
#include "framework.h"
#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

int fnGraphics()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	const char* window_title = "OpenGL window";
	const int window_width = 800;
	const int window_height = 800;
	GLFWwindow* window = glfwCreateWindow(window_width, window_height, window_title, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error loading window for Exercise1::easy_problem_3" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, window_width, window_height);
	glClearColor(1.0f, 0.65f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	const char* vertex_shader_source =
		"#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"out vec3 TexCoords;\n"
		"uniform mat4 view;\n"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"   TexCoords = aPos;\n"
		"   gl_Position = projection * view * vec4(aPos, 1.0);\n"
		"}\n";

	const char* fragment_shader_source =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"in vec3 TexCoords;\n"
		"uniform samplerCube skybox;\n"
		"void main()\n"
		"{\n"
		"	FragColor = texture(skybox, TexCoords);\n"
		"}\0";

	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	int has_shader_compiled;

	unsigned VAO;
	unsigned VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	unsigned vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertex_shader);
	glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &has_shader_compiled);
	if (!has_shader_compiled)
	{
		std::cout << "Error compiling vertex shader" << std::endl;
	}

	unsigned fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragment_shader);
	glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &has_shader_compiled);
	if (!has_shader_compiled)
	{
		std::cout << "Error compiling fragment shader" << std::endl;
	}

	unsigned shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);
	glGetShaderiv(shader_program, GL_COMPILE_STATUS, &has_shader_compiled);
	if (!has_shader_compiled)
	{
		std::cout << "Error linking shaders in shader program" << std::endl;
	}
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	std::vector<std::string> faces =
	{
		"../Main/skybox/right.jpg",
		"../Main/skybox/left.jpg",
		"../Main/skybox/top.jpg",
		"../Main/skybox/bottom.jpg",
		"../Main/skybox/front.jpg",
		"../Main/skybox/back.jpg"
	};

	unsigned int skyboxtexture;
	glGenTextures(1, &skyboxtexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxtexture);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glm::vec3 camera_pos(0.0f, 0.0f, 3.0f);
	glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_direction(camera_pos - camera_target);
	glm::vec3 camera_up(0.0f, 1.0f, 0.0f);
	glm::vec3 camera_right = glm::cross(glm::normalize(camera_direction), camera_up);

	float yaw = -90.0f;
	float pitch = 0.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	glm::vec3 camera_front = glm::normalize(direction);

	glm::mat4 view = glm::mat4(glm::mat3(glm::lookAt(camera_pos, camera_pos + camera_front, camera_up)));
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), 1.0f, 0.1f, 100.0f);

	glUseProgram(shader_program);
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader_program, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUseProgram(0);

	while (!glfwWindowShouldClose(window))
	{
		glDepthMask(GL_FALSE);
		glUseProgram(shader_program);
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxtexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}