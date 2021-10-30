#pragma once
#include <string>

struct BaseDialog
{
	std::string title;
	bool draw_together;
	BaseDialog(std::string title, bool draw_together)
	{
		this->title = title;
		this->draw_together = draw_together;
	}

	virtual void draw() = 0;
};