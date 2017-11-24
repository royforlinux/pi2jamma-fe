#pragma once

#include "ui/device/ui.hpp"
#include "core/Property.hpp"

class Theme
{
	public:

		static void initialize();

		PROPERTY(Rect, TitleRect);
		PROPERTY(Rect, MenuRect);
		PROPERTY(Rect, SnapsRect);
};