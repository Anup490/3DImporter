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

	ShaderProgram skyboxshader("../Main/test.vert", "../Main/test.frag");
	ShaderProgram modelshader("../Main/tex.vert", "../Main/tex.frag");

	vect::vec3 camera_pos(0.0f, 0.0f, 3.0f);
	vect::vec3 camera_up(0.0f, 1.0f, 0.0f);;

	Camera camera(window, camera_pos, camera_up);
	camera.set_view_matrix(skyboxshader, false);
	camera.set_projection_matrix(skyboxshader);

	CameraHandler handler(window);
	handler.add_camera(&camera);

	GLTFModel model("../Assets/crow/scene.gltf");
	window.enable_feature(Enum::DEPTH_TEST);

	vect::vec4 color(1.0f, 0.65f, 0.0f, 1.0f);

	bool draw_triangle = false;
	float size = 1.0f;
	float color_f[4] = { 1.0f, 0.75f, 0.8f, 1.0f };

	TextWidget textwidget("Configure triangle");
	SliderWidget sliderwidget("Size", &size, 0.5f, 2.0f);
	CheckboxWidget checkboxwidget("Draw triangle", &draw_triangle);
	ColorEdit4Widget coloreditwidget("Color", color_f);

	std::vector<BaseWidget*> widgets;
	widgets.push_back(&textwidget);
	widgets.push_back(&sliderwidget);
	widgets.push_back(&checkboxwidget);
	widgets.push_back(&coloreditwidget);

	ImGUI gui(&window, vect::vec2(550, 0), vect::vec2(250, 100));
	while (window.should_stay())
	{
		window.clear_color_buffer(color, Enum::COLOR_DEPTH_BUFFER_BIT);
		window.enable_depth_mask(false);
		camera.update_position();
		cubemap.draw(skyboxshader);
		window.enable_depth_mask(true);
		model.draw(modelshader, camera);
		gui.draw("Triangle settings", &widgets, Enum::DISABLE_MOVE_COLLAPSE_TITLE_RESIZE);
		window.run_swapbuffer_eventpoller();
	}
	return 0;
}