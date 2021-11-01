#include "pch.h"
#include "ImGUIWidgets.h"
#include "imgui/imgui.h"

void ImGUITextWidget::draw()
{
	ImGui::Text(label.c_str());
}

void ImGUISliderWidget::draw()
{
	ImGui::SliderFloat(label.c_str(), psize, min, max);
}

void ImGUICheckboxWidget::draw()
{
	ImGui::Checkbox(label.c_str(), pchecked);
}

void ImGUIColorEdit4Widget::draw()
{
	ImGui::ColorEdit4(label.c_str(), pcol);
}

void ImGUIInputTextWidget::draw()
{
	ImGui::InputText(label.c_str(), chars, IM_ARRAYSIZE(chars));
}

void ImGUIButtonWidget::draw()
{
	if (ImGui::Button(label.c_str()))
	{
		callback_func();
	}
}