#include "pch.h"
#include "Im_GUI.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "Window.h" 
#include "Enum.h"
#include "Widgets.h"
#include <vector>

ImGUI::ImGUI(Window* pwindow, vect::vec2 position, vect::vec2 size)
{
	this->pwindow = pwindow;
	this->position = position;
	this->size = size;
	this->pwidgets = new std::vector<BaseWidget*>;
	initialize();
}

ImGUI::~ImGUI()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	delete pwidgets;
}

void ImGUI::add_widget(BaseWidget* pwidget)
{
	pwidgets->push_back(pwidget);
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
		set_widget(pwidget);
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

void ImGUI::set_widget(BaseWidget* pwidget)
{
	switch (pwidget->get_type())
	{
		case WidgetType::TEXT:
		{
			TextWidget* ptextwidget = static_cast<TextWidget*>(pwidget);
			ImGui::Text(ptextwidget->label.c_str());
			break;
		}
		case WidgetType::SLIDER:
		{
			SliderWidget* psliderwidget = static_cast<SliderWidget*>(pwidget);
			ImGui::SliderFloat(psliderwidget->label.c_str(), psliderwidget->psize, psliderwidget->min, psliderwidget->max);
			break;
		}
		case WidgetType::CHECKBOX:
		{
			CheckboxWidget* pcheckboxwidget = static_cast<CheckboxWidget*>(pwidget);
			ImGui::Checkbox(pcheckboxwidget->label.c_str(), pcheckboxwidget->pchecked);
			break;
		}
		case WidgetType::COLOREDIT4:
		{
			ColorEdit4Widget* pcoloreditwidget = static_cast<ColorEdit4Widget*>(pwidget);
			ImGui::ColorEdit4(pcoloreditwidget->label.c_str(), pcoloreditwidget->pcol);
			break;
		}
		case WidgetType::INPUTTEXT:
		{
			InputTextWidget* pinputtextwidget = static_cast<InputTextWidget*>(pwidget);
			ImGui::InputText(pinputtextwidget->label.c_str(), pinputtextwidget->chars, IM_ARRAYSIZE(pinputtextwidget->chars));
			break;
		}
		case WidgetType::BUTTON:
		{
			ButtonWidget* pbuttonwidget = static_cast<ButtonWidget*>(pwidget);
			if (ImGui::Button(pbuttonwidget->label.c_str()))
			{
				pbuttonwidget->callback_func();
			}
			break;
		}
	}
}