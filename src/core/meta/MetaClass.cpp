#include "core/meta/MetaClass.hpp"
#include "core/meta/Meta.hpp"
#include "core/debug.hpp"

MetaClassBase::MetaClassBase(CStrArg name)
	: MetaType(name)
{
}

MetaClassProperty::MetaClassProperty(
	MetaClassBase* pMetaClassBase,
	MetaType* pPropertyType,
	CStrArg name)
	: mName(name)
	, mpPropertyType(pPropertyType)
	, mTreeNode(this)
{
	ASSERT(nullptr != pMetaClassBase);
	ASSERT(nullptr != pPropertyType);
	
	pMetaClassBase->addProperty(this);
}

Result MetaClassBase::load(void* object, const ref<Json>& refJson)
{
	ref<JsonClass> refClass;
	Result r = Json::asClass(refClass,refJson);
	if(r.peekFailed()) {
		return r;
	}
	for(auto&& prop: mProperties) {
		ref<Json> refProperty =
			refClass->getMember(prop->mItem->getName());
		
		if(refProperty.isNull()) {
			continue;
		}

		return prop->mItem->load(this, refProperty);
	}

	return Result::makeSuccess();
}



