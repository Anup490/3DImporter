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
#include "Mesh.h"
#include "Texture.h"
#include "GLTFModel.h"

int fnGraphics()
{
	Window window("3DImporter", 1024, 768);

	std::vector<std::string> faces =
	{
		"../Assets/skybox/right.jpg",
		"../Assets/skybox/left.jpg",
		"../Assets/skybox/top.jpg",
		"../Assets/skybox/bottom.jpg",
		"../Assets/skybox/front.jpg",
		"../Assets/skybox/back.jpg"
	};

	Cubemap cubemap(faces);

	ShaderProgram skyboxshader("../Main/test.vert", "../Main/test.frag");
	ShaderProgram modelshader("../Main/tex.vert", "../Main/tex.frag");

	glm::vec3 camera_pos(0.0f, 0.0f, 3.0f);
	glm::vec3 camera_up(0.0f, 1.0f, 0.0f);;

	Camera camera(window, camera_pos, camera_up);
	camera.set_view_matrix(skyboxshader, false);
	camera.set_projection_matrix(skyboxshader);

	CameraHandler handler(window);
	handler.add_camera(&camera);

	GLTFModel model("../Assets/crow/scene.gltf");

	glEnable(GL_DEPTH_TEST);

	glm::vec4 color(1.0f, 0.65f, 0.0f, 1.0f);

	while (window.should_stay())
	{
		window.clear_color_buffer(color, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		window.enable_depth_mask(FALSE);
		camera.update_position();
		cubemap.draw(skyboxshader);
		window.enable_depth_mask(TRUE);
		model.draw(modelshader, camera);
		window.run_swapbuffer_eventpoller();
	}
	return 0;
}