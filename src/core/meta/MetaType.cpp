#include "core/meta/MetaType.hpp"

#include "core/meta/Meta.hpp"


MetaType::MetaType(CStr name, const std::type_info& typeInfo)
	: mName(name)
	, mTypeInfo(typeInfo)
	, mByNameTreeNode(this)
	, mByTypeInfoTreeNode(this) {
	Meta::get().addType(this);
}

MetaType::~MetaType() 
{
	Meta::get().removeType(this);
}