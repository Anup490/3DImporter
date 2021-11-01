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
	vect::vec2 position;
	vect::vec2 size;
	std::vector<BaseWidget*>* pwidgets;
	std::vector<BaseDialog*>* pdialogs;
	void initialize();
public:
	ImGUI(Window* pwindow, vect::vec2 position, vect::vec2 size);
	~ImGUI();
	void add_widget(BaseWidget* pwidget);
	void add_dialog(BaseDialog* pdialog);
	void draw(const char* title, Enum flag);
	vect::vec2 get_position();
	vect::vec2 get_size();
};