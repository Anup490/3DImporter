#include "pch.h"
#include "ImGUIDialogs.h"
#include "imgui/imgui.h"
#include "imgui/imfilebrowser.h"

ImGUIFileBrowserDialog::ImGUIFileBrowserDialog(std::string title, function* dismiss_callback) : BaseDialog(title, true)
{
	this->pfilebrowser = new ImGui::FileBrowser;
	this->pfilebrowser->SetTitle("File Browser");
	this->pfilebrowser->SetTypeFilters({ ".gltf" });
	this->dismiss_callback = dismiss_callback;
}

ImGUIFileBrowserDialog::~ImGUIFileBrowserDialog()
{
	delete pfilebrowser;
}

void ImGUIFileBrowserDialog::open()
{
	pfilebrowser->Open();
	is_open = true;
}

void ImGUIFileBrowserDialog::draw()
{
	if (is_open)
	{
		pfilebrowser->Display();
		if (pfilebrowser->HasSelected())
		{
			has_selected = true;
			file_path = pfilebrowser->GetSelected().string();
		}
	}
	if (is_open && (has_selected || !(pfilebrowser->IsOpened())))
	{
		frame_count++;
		if (frame_count == 3)
		{
			dismiss_callback(file_path, has_selected);
			has_selected = false;
			is_open = false;
			frame_count = 0;
		}
	}
}