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

MetaType* Meta::findType(const std::type_info& typeInfo) {
	MetaType* pMetaType = safeDeRef(mTypesByTypeInfo.find(typeInfo));
	ASSERTFMT(
		(nullptr != pMetaType),
		"%s is not registered with the meta system.",
		typeInfo.name());
	return pMetaType;
}

MetaType* Meta::findType(CStrArg name) {
	MetaType* pMetaType = safeDeRef(mTypesByName.find(name));
	ASSERTFMT(
		(nullptr != pMetaType),
		"%s is not registered with the meta system.",
		name.c_str());
	return pMetaType;	
}

