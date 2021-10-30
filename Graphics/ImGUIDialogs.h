#pragma once
#include "Dialogs.h"

namespace ImGui
{
	class FileBrowser;
}

struct ImGUIFileBrowserDialog : BaseDialog
{
	ImGui::FileBrowser* pfilebrowser;
	bool is_open = false;
	bool has_selected = false;
	std::string file_path;
	ImGUIFileBrowserDialog(std::string title);
	~ImGUIFileBrowserDialog();
	void open();
	void draw() override;
	std::string get_path();
};