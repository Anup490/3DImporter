#pragma once
#include "Widgets.h"

struct ImGUITextWidget : BaseWidget
{
	ImGUITextWidget(std::string label) : BaseWidget(label) {}

	virtual WidgetType get_type() override
	{
		return WidgetType::TEXT;
	}

	virtual void draw() override;
};

struct ImGUISliderWidget : BaseWidget
{
	float min, max;
	float* psize;

	ImGUISliderWidget(std::string label, float* psize, float min, float max) : BaseWidget(label)
	{
		this->psize = psize;
		this->min = min;
		this->max = max;
	}

	virtual WidgetType get_type() override
	{
		return WidgetType::SLIDER;
	}

	virtual void draw() override;
};

struct ImGUICheckboxWidget : BaseWidget
{
	bool* pchecked;

	ImGUICheckboxWidget(std::string label, bool* pchecked) : BaseWidget(label)
	{
		this->label = label;
		this->pchecked = pchecked;
	}

	virtual WidgetType get_type() override
	{
		return WidgetType::CHECKBOX;
	}

	virtual void draw() override;
};

struct ImGUIColorEdit4Widget : BaseWidget
{
	float* pcol;

	ImGUIColorEdit4Widget(std::string label, float col[4]) : BaseWidget(label)
	{
		this->label = label;
		this->pcol = col;
	}

	virtual WidgetType get_type() override
	{
		return WidgetType::COLOREDIT4;
	}

	virtual void draw() override;
};

struct ImGUIInputTextWidget : ImGUITextWidget
{
	char chars[100] = "";

	ImGUIInputTextWidget(std::string label = "", std::string init_text = "") : ImGUITextWidget(label)
	{
		int length = init_text.length();
		const char* ptext = init_text.c_str();
		for (int i = 0; i < length; i++)
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

	virtual void draw() override;
};

struct ImGUIButtonWidget : BaseWidget
{
	using callback = void(void);
	callback* callback_func;

	ImGUIButtonWidget(std::string label, callback callback_func) : BaseWidget(label)
	{
		this->callback_func = callback_func;
	}

	virtual WidgetType get_type() override
	{
		return WidgetType::BUTTON;
	}

	virtual void draw() override;
};