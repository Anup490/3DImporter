#include "pch.h"
#include "Im_GUI.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Window.h" 
#include "Enum.h"
#include "Widgets.h"
#include "Dialogs.h"
#include <vector>

ImGUI::ImGUI(Window* pwindow, vect::vec2 position, vect::vec2 size)
{
	this->pwindow = pwindow;
	this->position = position;
	this->size = size;
	this->pwidgets = new std::vector<BaseWidget*>;
	this->pdialogs = new std::vector<BaseDialog*>;
	initialize();
}

ImGUI::~ImGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	delete pwidgets;
	delete pdialogs;
}

void ImGUI::add_widget(BaseWidget* pwidget)
{
	pwidgets->push_back(pwidget);
}

void ImGUI::add_dialog(BaseDialog* pdialog)
{
	pdialogs->push_back(pdialog);
}

void ImGUI::draw(const char* title, Enum flag)
{
	bool open = true;
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::SetNextWindowPos(ImVec2(position.x, position.y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y), ImGuiCond_Always);
	ImGui::Begin(title, &open, flag.val);
	for (BaseWidget* pwidget : *pwidgets)
	{
		pwidget->draw();
	}
	for (BaseDialog* pdialog : *pdialogs)
	{
		pdialog->draw();
	}
	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

vect::vec2 ImGUI::get_position()
{
	return position;
}

vect::vec2 ImGUI::get_size()
{
	return size;
}

void ImGUI::initialize()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigWindowsMoveFromTitleBarOnly = true;
	io.ConfigWindowsResizeFromEdges = false;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(pwindow->get_window(), true);
	ImGui_ImplOpenGL3_Init("#version 330");
}