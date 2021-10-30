#include "pch.h"
#include "ImGUIDialogs.h"
#include "imgui/imgui.h"
#include "imgui/imfilebrowser.h"

ImGUIFileBrowserDialog::ImGUIFileBrowserDialog(std::string title) : BaseDialog(title)
{
	this->pfilebrowser = new ImGui::FileBrowser;
	this->pfilebrowser->SetTitle("File Browser");
	this->pfilebrowser->SetTypeFilters({ ".gltf" });
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

#include <iostream>

void ImGUIFileBrowserDialog::draw()
{
	if (is_open)
	{
		pfilebrowser->Display();
		if (pfilebrowser->HasSelected())
		{
			is_open = false;
			has_selected = true;
			file_path = pfilebrowser->GetSelected().string();
			pfilebrowser->ClearSelected();
		}
	}
}

std::string ImGUIFileBrowserDialog::get_path()
{
	has_selected = false;
	return file_path;
}