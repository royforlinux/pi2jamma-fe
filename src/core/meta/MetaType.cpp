#include "core/meta/MetaType.hpp"

#include "core/meta/Meta.hpp"

MetaType::MetaType(CStr name)
	: mName(name)
	, mByNameTreeNode(this)
	, mByTypeInfoTreeNode(this) {
	Meta::get().addType(this);
}