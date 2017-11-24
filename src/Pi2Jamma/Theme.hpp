#pragma once

#include "ui/device/ui.hpp"
#include "core/Property.hpp"

class Theme
{
	public:

		static void initialize();

		Rect mTitleRect;
		Rect mMenuRect;
		Rect mSnapsRect;
};