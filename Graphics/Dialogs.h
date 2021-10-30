#pragma once
#include <string>

struct BaseDialog
{
	std::string title;
	BaseDialog(std::string title)
	{
		this->title = title;
	}

	virtual void draw() = 0;
};