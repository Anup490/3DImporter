#pragma once
#include "BaseHeader.h"
#include "Vectors.h"

struct BaseWidget;
struct BaseDialog;
struct Enum;
class Window;

class ImGUI
{
	Window* pwindow;
	graphics::vec2 position;
	graphics::vec2 size;
	std::vector<BaseWidget*>* pwidgets;
	std::vector<BaseDialog*>* pdialogs;
	void initialize();
public:
	ImGUI(Window* pwindow, graphics::vec2 position, graphics::vec2 size);
	~ImGUI();
	void add_widget(BaseWidget* pwidget);
	void add_dialog(BaseDialog* pdialog);
	void draw(const char* title, Enum flag);
	graphics::vec2 get_position();
	graphics::vec2 get_size();
};