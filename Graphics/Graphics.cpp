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
	Window window("OpenGLTest", 1024, 768);
	window.clear_color_buffer(1.0f, 0.65f, 0.0f, 1.0f);

	std::vector<Vertex> skyboxVertices = {       
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},

		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},

		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},

		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},

		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f,  1.0f)},
		Vertex{glm::vec3(-1.0f,  1.0f, -1.0f)},

		Vertex{glm::vec3(-1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, -1.0f)},
		Vertex{glm::vec3(-1.0f, -1.0f,  1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f,  1.0f)}
	};

	int has_shader_compiled;

	std::vector<std::string> faces =
	{
		"../Assets/skybox/right.jpg",
		"../Assets/skybox/left.jpg",
		"../Assets/skybox/top.jpg",
		"../Assets/skybox/bottom.jpg",
		"../Assets/skybox/front.jpg",
		"../Assets/skybox/back.jpg"
	};

	Cubemap cubemap(
		faces, 
		skyboxVertices,
		TEXTURE_WRAP_CLAMP_TO_EDGE, 
		TEXTURE_WRAP_CLAMP_TO_EDGE, 
		TEXTURE_WRAP_CLAMP_TO_EDGE, 
		TEXTURE_FILTER_LINEAR, 
		TEXTURE_FILTER_LINEAR
	);

	ShaderProgram shader("../Main/test.vert", "../Main/test.frag");
	ShaderProgram wallshader("../Main/tex.vert", "../Main/tex.frag");

	glm::vec3 camera_pos(0.0f, 0.0f, 3.0f);
	glm::vec3 camera_target(0.0f, 0.0f, 0.0f);
	glm::vec3 camera_up(0.0f, 1.0f, 0.0f);;

	Camera camera(window, camera_pos, camera_target, camera_up);
	camera.set_view_matrix(shader, false);
	camera.set_projection_matrix(shader);

	CameraHandler handler(window);
	handler.add_camera(&camera);

	std::vector<Vertex> verticesParallax =
	{
		Vertex{glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(1.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 0.0f)}
	};

	std::vector<GLuint> indicesParallax =
	{
		0, 1, 2,
		0, 2, 3
	};

	/*std::vector<Texture> textures;
	Texture t1("../Assets/wall.png", "diffuse",0, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE, GL_NEAREST, GL_NEAREST);
	textures.push_back(t1);*/

	//Mesh mesh(verticesParallax, indicesParallax, textures);
	GLTFModel model("../Assets/bunny/scene.gltf");

	while (window.should_stay())
	{
		window.enable_depth_mask(FALSE);
		camera.update_position();
		cubemap.draw(shader);
		//mesh.draw(wallshader, camera);
		model.draw(wallshader,camera);
		window.enable_depth_mask(TRUE);
		window.run_swapbuffer_eventpoller();
	}
	return 0;
}