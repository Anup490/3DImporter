#include "pch.h"
#include "framework.h"
#include <iostream>
#include <glad/glad.h>
#include <vector>
#include "Window.h"
#include "ShaderProgram.h"
#include "VertexBufferObject.h"
#include "VertexArrayObject.h"
#include "Camera.h"
#include "CameraHandler.h"
#include "Cubemap.h"
#include "Enums.h"

int fnGraphics()
{
	Window window("OpenGLTest", 1024, 768);
	window.clear_color_buffer(1.0f, 0.65f, 0.0f, 1.0f);

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

	VertexBufferObject VBO(skyboxVertices, sizeof(skyboxVertices), STATIC_USAGE);
	VertexArrayObject VAO;
	VAO.link_vbo(VBO, 0, 3, FLOAT, FALSE, 3 * sizeof(float), (void*)0);

	std::vector<std::string> faces =
	{
		"../Main/skybox/right.jpg",
		"../Main/skybox/left.jpg",
		"../Main/skybox/top.jpg",
		"../Main/skybox/bottom.jpg",
		"../Main/skybox/front.jpg",
		"../Main/skybox/back.jpg"
	};

	Cubemap cubemap(
		faces, 
		TEXTURE_WRAP_CLAMP_TO_EDGE, 
		TEXTURE_WRAP_CLAMP_TO_EDGE, 
		TEXTURE_WRAP_CLAMP_TO_EDGE, 
		TEXTURE_FILTER_LINEAR, 
		TEXTURE_FILTER_LINEAR, 
		COLOR_CHANNEL_RGB
	);

	ShaderProgram shader("../Graphics/test.vert", "../Graphics/test.frag");

	glm::vec3 camera_pos(0.0f, 0.0f, 3.0f);
	glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_up(0.0f, 1.0f, 0.0f);;

	Camera camera(window, camera_pos, camera_target, camera_up);
	camera.set_view_matrix(shader, false);
	camera.set_projection_matrix(shader);

	CameraHandler handler(window);
	handler.add_camera(&camera);

	while (window.should_stay())
	{
		window.enable_depth_mask(FALSE);
		shader.activate();
		camera.update_position();
		VAO.bind();
		cubemap.bind();
		glDrawArrays(TRIANGLES, 0, 36);
		window.enable_depth_mask(TRUE);
		window.run_swapbuffer_eventpoller();
	}
	return 0;
}