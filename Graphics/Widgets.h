#pragma once
#include <string>

enum class WidgetType
{
	TEXT, SLIDER, CHECKBOX, COLOREDIT4
};

struct BaseWidget
{
	virtual WidgetType get_type() = 0;
};

struct TextWidget : BaseWidget 
{
	std::string label;

	TextWidget(std::string label)
	{
		this->label = label;
	}

	WidgetType get_type() override
	{
		return WidgetType::TEXT;
	}
};

struct SliderWidget : BaseWidget
{
	std::string label;
	float min, max;
	float* psize;

	SliderWidget(std::string label, float* psize, float min, float max)
	{
		this->label = label;
		this->psize = psize;
		this->min = min;
		this->max = max;
	}

	WidgetType get_type() override
	{
		return WidgetType::SLIDER;
	}
};

struct CheckboxWidget : BaseWidget
{
	std::string label;
	bool* pchecked;

	CheckboxWidget(std::string label, bool* pchecked)
	{
		this->label = label;
		this->pchecked = pchecked;
	}

	WidgetType get_type() override
	{
		return WidgetType::CHECKBOX;
	}
};

struct ColorEdit4Widget : BaseWidget
{
	std::string label;
	float* pcol;

	ColorEdit4Widget(std::string label, float col[4])
	{
		this->label = label;
		this->pcol = col;
	}

	WidgetType get_type() override
	{
		return WidgetType::COLOREDIT4;
	}
};