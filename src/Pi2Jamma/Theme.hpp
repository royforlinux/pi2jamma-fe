#pragma once

#include "ui/ui.hpp"
#include "ui/HorizontalAlignment.hpp"
#include "core/Property.hpp"

class Theme
{
	public:

		static void initialize();

		PROPERTY(Rect, TitleRect);
		PROPERTY(Color, TitleTextColor);
		PROPERTY(HorizontalAlignment, TitleAlignment);
		
		PROPERTY(Rect, SnapsRect);

		PROPERTY(Rect, MenuRect);
		PROPERTY(Color, MenuTextColor);
		PROPERTY(Color, MenuTextHighlightColor);
		
		PROPERTY(size_t, MenuTextSize);
		PROPERTY(HorizontalAlignment, MenuTextAlignment);

};