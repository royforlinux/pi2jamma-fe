#include "Pi2Jamma/Theme.hpp"

#include "core/meta/Meta.hpp"

void Theme::initialize() {

	META_CLASS(Theme);
	META_CLASS_FIELD(Theme, SnapsRect);
	META_CLASS_FIELD(Theme, MenuRect);
	META_CLASS_FIELD(Theme, TitleRect);
}
