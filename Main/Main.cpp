#include <iostream>
#include <vector>
#include "Window.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "CameraHandler.h"
#include "Cubemap.h"
#include "Enum.h"
#include "GLTFModel.h"
#include "Widgets.h"
#include "Im_GUI.h"

int main()
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

	ShaderProgram skyboxshader("test.vert", "test.frag");
	ShaderProgram modelshader("tex.vert", "tex.frag");

	GLTFModel model("../Assets/crow/scene.gltf");
	window.enable_feature(Enum::DEPTH_TEST);

	vect::vec4 color(1.0f, 0.65f, 0.0f, 1.0f);

	char path[100] = "";
	TextWidget textwidgettitle("3D Importer");
	TextWidget textwidgetpath("Path :: ");
	InputTextWidget inputtextwidget("", "");

	ImGUI gui(&window, vect::vec2(774, 668), vect::vec2(250, 100));
	gui.add_widget(&textwidgettitle);
	gui.add_widget(&textwidgetpath);
	gui.add_widget(&inputtextwidget);

	vect::vec3 camera_pos(0.0f, 0.0f, 3.0f);
	vect::vec3 camera_up(0.0f, 1.0f, 0.0f);;

	Camera camera(window, gui, camera_pos, camera_up);
	camera.set_view_matrix(skyboxshader, false);
	camera.set_projection_matrix(skyboxshader);

	CameraHandler handler(window);
	handler.add_camera(&camera);

	while (window.should_stay())
	{
		window.clear_color_buffer(color, Enum::COLOR_DEPTH_BUFFER_BIT);
		window.enable_depth_mask(false);
		camera.update_position();
		cubemap.draw(skyboxshader);
		window.enable_depth_mask(true);
		model.draw(modelshader, camera);
		gui.draw("Triangle settings", Enum::DISABLE_MOVE_COLLAPSE_TITLE_RESIZE);
		window.run_swapbuffer_eventpoller();
	}
	return 0;
}