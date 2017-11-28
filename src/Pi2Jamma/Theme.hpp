#pragma once

#include "ui/device/ui.hpp"
#include "ui/HorizontalAlignment.hpp"

class Theme
{
	public:

		static void initialize();

		Rect mTitleRect;
		Color mTitleTextColor;
		HorizontalAlignment mTitleAlignment;
		
		Rect mSnapsRect;

		Rect mMenuRect;
		Color mMenuTextColor;
		Color mMenuTextHighlightColor;
		
		size_t mMenuTextSize;
		HorizontalAlignment mMenuTextAlignment;
};