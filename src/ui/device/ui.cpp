#include "ui/device/ui.hpp"

#include "core/meta/Meta.hpp"

namespace ui
{

void initialize() {
	META_ENUM(Key);
	META_ENUM_VALUE(Key, DownArrow);
	META_ENUM_VALUE(Key, UpArrow);
	META_ENUM_VALUE(Key, Escape);
	META_ENUM_VALUE(Key, Space);

	META_CLASS(Rect);

	META_CLASS_PROPERTY(Rect, X);
	META_CLASS_PROPERTY(Rect, Y);
	META_CLASS_PROPERTY(Rect, Width);
	META_CLASS_PROPERTY(Rect, Height);

}

} // namespac ui
