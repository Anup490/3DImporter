#pragma once
#include "BaseHeader.h"
#include "Vectors.h"

struct BaseWidget;
struct Enum;
class Window;

class ImGUI
{
	Window* pwindow;
	vect::vec2 position;
	vect::vec2 size;
	void initialize();
	void set_widget(BaseWidget* pwidget);
public:
	ImGUI(Window* pwindow, vect::vec2 position, vect::vec2 size);
	~ImGUI();
	void draw(const char* title, std::vector<BaseWidget*>* pwidgets, Enum flag);
};