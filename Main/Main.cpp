#include <iostream>
#include <vector>
#include "Window.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "CameraHandler.h"
#include "Cubemap.h"
#include "Enum.h"
#include "GLTFModel.h"
#include "ImGUIWidgets.h"
#include "ImGUIDialogs.h"
#include "Im_GUI.h"

ImGUIFileBrowserDialog* pfiledialog = 0;
GLTFModel* pmodel = 0;
Camera* pcamera = 0;

void load_model(std::string path);
std::string replace_slash(std::string path);

void button_callback()
{
	pfiledialog->open();
	pcamera->enable(false);
}

void file_browser_dismiss_callback(std::string path, bool has_selected)
{
	if (has_selected)
	{
		load_model(path);
	}
	pcamera->enable(true);
}

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

	pmodel = new GLTFModel("../Assets/crow/scene.gltf");
	window.enable_feature(Enum::DEPTH_TEST);

	vect::vec4 color(1.0f, 0.65f, 0.0f, 1.0f);

	char path[100] = "";
	ImGUITextWidget textwidgetpath("Browse GLTF file : ");
	ImGUIButtonWidget buttonwidget("BROWSE", button_callback);

	ImGUIFileBrowserDialog filedialog("File Browser", file_browser_dismiss_callback);
	pfiledialog = &filedialog;

	ImGUIProgressDialog progressdialog("Loading...", window.get_dimensions(), &filedialog.has_selected);

	ImGUI gui(&window, vect::vec2(424, 688), vect::vec2(600, 80));
	gui.add_widget(&textwidgetpath);
	gui.add_widget(&buttonwidget);
	gui.add_dialog(&filedialog);
	gui.add_dialog(&progressdialog);

	vect::vec3 camera_pos(0.0f, 0.0f, 3.0f);
	vect::vec3 camera_up(0.0f, 1.0f, 0.0f);;

	Camera camera(window, gui, camera_pos, camera_up);
	camera.set_view_matrix(skyboxshader, false);
	camera.set_projection_matrix(skyboxshader);
	pcamera = &camera;

	CameraHandler handler(window);
	handler.add_camera(&camera);
	int count = 0;
	while (window.should_stay())
	{
		window.clear_color_buffer(color, Enum::COLOR_DEPTH_BUFFER_BIT);
		camera.update_position();
		cubemap.draw(skyboxshader, window);
		if(pmodel)
			pmodel->draw(modelshader, camera);
		gui.draw("3D Importer", Enum::DISABLE_MOVE_COLLAPSE_TITLE_RESIZE);
		window.run_swapbuffer_eventpoller();
	}
	delete pmodel;
	return 0;
}

void load_model(std::string path)
{
	std::string formatted_path = replace_slash(path);
	GLTFModel* pNewModel = new GLTFModel(formatted_path.c_str());
	if (pNewModel->load_failure)
	{
		std::cout << "failure loading from :: " << formatted_path << std::endl;
		delete pNewModel;
	}
	else
	{
		delete pmodel;
		pmodel = pNewModel;
		pcamera->reset();
	}
}