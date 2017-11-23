#include "Pi2Jamma/Theme.hpp"

#include "core/meta/Meta.hpp"

void Theme::initialize()
{
	META_CLASS(Theme);
	META_PROPERTY(Theme, SnapsRect);
	//META_PROPERTY(c, MenuRect);
	//META_PROPERTY(c, SnapsRect);
}