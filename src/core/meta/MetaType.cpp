#include "core/meta/MetaType.hpp"

#include "core/meta/Meta.hpp"

MetaType::MetaType(CStr name)
	: mName(name)
	, mByNameTreeNode(this)
	, mByTypeInfoTreeNode(this) {
	LogFmt("AddingType: %s\n", name.c_str());
	Meta::get().addType(this);
}