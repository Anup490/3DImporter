#pragma once
#include <string>

enum class WidgetType
{
	TEXT, SLIDER, CHECKBOX, COLOREDIT4, INPUTTEXT
};

struct BaseWidget
{
	std::string label;
	BaseWidget(std::string label)
	{
		this->label = label;
	}
	virtual WidgetType get_type() = 0;
};

struct TextWidget : BaseWidget 
{
	TextWidget(std::string label) : BaseWidget(label) {}

	virtual WidgetType get_type() override
	{
		return WidgetType::TEXT;
	}
};

struct SliderWidget : BaseWidget
{
	float min, max;
	float* psize;

	SliderWidget(std::string label, float* psize, float min, float max) : BaseWidget(label)
	{
		this->psize = psize;
		this->min = min;
		this->max = max;
	}

	virtual WidgetType get_type() override
	{
		return WidgetType::SLIDER;
	}
};

struct CheckboxWidget : BaseWidget
{
	bool* pchecked;

	CheckboxWidget(std::string label, bool* pchecked) : BaseWidget(label) 
	{
		this->label = label;
		this->pchecked = pchecked;
	}

	virtual WidgetType get_type() override
	{
		return WidgetType::CHECKBOX;
	}
};

struct ColorEdit4Widget : BaseWidget
{
	float* pcol;

	ColorEdit4Widget(std::string label, float col[4]) : BaseWidget(label) 
	{
		this->label = label;
		this->pcol = col;
	}

	virtual WidgetType get_type() override
	{
		return WidgetType::COLOREDIT4;
	}
};

struct InputTextWidget : TextWidget
{
	char chars[100] = "";

	InputTextWidget(std::string label, std::string init_text) : TextWidget(label)
	{
		int length = init_text.length();
		const char* ptext = init_text.c_str();
		for (int i=0; i<length; i++)
		{
			chars[i] = *(ptext + i);
		}
	}

	virtual WidgetType get_type() override
	{
		return WidgetType::INPUTTEXT;
	}

	std::string get_text()
	{
		return std::string(chars);
	}
};