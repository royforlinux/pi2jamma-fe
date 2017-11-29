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

	LogFmt(
		"registering meta-type: name: '%s' typeinfo: '%s\n",
		pMetaType->getName().c_str(),
		pMetaType->getTypeInfo().name());

	mTypesByName.insert(pMetaType->mByNameTreeNode);
	mTypesByTypeInfo.insert(pMetaType->mByTypeInfoTreeNode);
}

void Meta::removeType(MetaType* pMetaType)
{
	ASSERT(nullptr != pMetaType);

	mTypesByName.remove(pMetaType->mByNameTreeNode);
	mTypesByTypeInfo.remove(pMetaType->mByTypeInfoTreeNode);
}

MetaType* Meta::findType(const std::type_info& typeInfo) {
	MetaType* pMetaType = safeDeRef(mTypesByTypeInfo.findItem(typeInfo));
	ASSERTFMT(
		(nullptr != pMetaType),
		"%s is not registered with the meta system.",
		typeInfo.name());
	return pMetaType;
}

MetaType* Meta::findType(CStrArg name) {
	MetaType* pMetaType = safeDeRef(mTypesByName.findItem(name));
	ASSERTFMT(
		(nullptr != pMetaType),
		"%s is not registered with the meta system.",
		name.c_str());
	return pMetaType;	
}

