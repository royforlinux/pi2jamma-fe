#include "Pi2Jamma/Theme.hpp"

#include "core/meta/Meta.hpp"

void Theme::initialize() {

	META_CLASS(Theme);
	META_CLASS_PROPERTYGS(Theme, Rect, SnapsRect);
	META_CLASS_PROPERTYGS(Theme, Rect, MenuRect);
	META_CLASS_PROPERTYGS(Theme, Rect, TitleRect);
	META_CLASS_PROPERTYGS(Theme, Rect, MenuRect);
}
