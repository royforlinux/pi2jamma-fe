#include "core/meta/MetaClass.hpp"

MetaClassPropertyBase::MetaClassPropertyBase(
	MetaClassBase* pMetaClassBase,
	CStrArg name)
	: mName(name)
	, mTreeNode(this)
{
	pMetaClassBase->addProperty(this);
}

Result MetaClassBase::load(LoadTextContext& loadTextContext)
{
	return Result::makeFailureNotImplemented();
}

