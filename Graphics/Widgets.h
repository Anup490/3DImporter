#pragma once
#include <string>

enum class WidgetType
{
	TEXT, SLIDER, CHECKBOX, COLOREDIT4, INPUTTEXT, BUTTON
};

struct BaseWidget
{
	std::string label;
	BaseWidget(std::string label)
	{
		this->label = label;
	}
	virtual WidgetType get_type() = 0;
	virtual void draw() = 0;
};