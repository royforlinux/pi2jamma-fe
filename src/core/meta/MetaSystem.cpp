#include "core/meta/Meta.hpp"

#include "core/meta/MetaPrimitive.hpp"

Meta* Meta::spSingleton = nullptr;

void Meta::initialize() {
	new Meta();
}

Meta::Meta()
{
	spSingleton = this;

	META_PRIMITIVE(char);
	META_PRIMITIVE2(unsigned, char);
	META_PRIMITIVE(short);
	META_PRIMITIVE2(unsigned, short);
	META_PRIMITIVE(int);
	META_PRIMITIVE2(unsigned, int);
	META_PRIMITIVE(long);
	META_PRIMITIVE2(unsigned, long);
	META_PRIMITIVE2(long, long);
	META_PRIMITIVE3(unsigned, long, long);

	META_PRIMITIVE(float);
	META_PRIMITIVE(double);
}

void Meta::addType(MetaType* pMetaType)
{
	ASSERT(nullptr != pMetaType);

	mTypesByName.insert(pMetaType->mByNameTreeNode);
	mTypesByTypeInfo.insert(pMetaType->mByTypeInfoTreeNode);
}


