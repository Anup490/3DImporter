#include "pch.h"
#include "ImGUIDialogs.h"
#include "Enum.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

ImGUIProgressDialog::ImGUIProgressDialog(std::string title, graphics::vec2 window_dim, bool* pshow) : BaseDialog(title, false)
{
	this->position = graphics::vec2((window_dim.x/2) - (size_x / 2), (window_dim.y/2) - (size_y / 2));
	this->pshow = pshow;
}

void ImGUIProgressDialog::draw()
{
	if (*pshow)
	{
		bool open = false;
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::SetNextWindowPos(ImVec2(position.x, position.y), ImGuiCond_Always);
		ImGui::SetNextWindowSize(ImVec2(size_x, size_y), ImGuiCond_Always);
		ImGui::Begin(title.c_str(), &open, Enum::DISABLE_MOVE_COLLAPSE_TITLE_RESIZE.val);
		ImGui::Text(title.c_str());
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}