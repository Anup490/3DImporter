#pragma once
#include "Dialogs.h"
#include "Vectors.h"

namespace ImGui
{
	class FileBrowser;
}

struct ImGUIFileBrowserDialog : BaseDialog
{	
	using function = void(std::string);
	bool has_selected = false;
	ImGUIFileBrowserDialog(std::string title, function* dismiss_callback);
	~ImGUIFileBrowserDialog();
	void open();
	void draw() override;
private:
	ImGui::FileBrowser* pfilebrowser;
	bool is_open = false;
	std::string file_path;
	function* dismiss_callback;
	int frame_count = 0;
};

struct ImGUIProgressDialog : BaseDialog
{
	ImGUIProgressDialog(std::string title, vect::vec2 window_dim, bool* pshow);
	void draw() override;
private:
	vect::vec2 position;
	bool* pshow;
	const float size_x = 86.0f;
	const float size_y = 30.0f;
};