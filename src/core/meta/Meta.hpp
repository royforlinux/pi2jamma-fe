#pragma once

#include "core/meta/MetaEnum.hpp"
#include "core/meta/MetaClass.hpp"

#include <unordered_map>
#include <typeinfo>
#include <typeindex>

class Meta
{
public:

	static Meta& get() { return sSingleton; }

	void addEnum(MetaEnumBase* pMetaEnumBase)
	{
		mTypesByName.insert(pMetaEnumBase->mByNameTreeNode);
		mTypesByTypeInfo.insert(pMetaEnumBase->mByTypeInfoTreeNode);
	}

	MetaType* findType(const std::type_info& typeInfo) {
		return safeDeRef(mTypesByTypeInfo.find(typeInfo));
	}

	MetaType* findType(const CStr& name) {
		return safeDeRef(mTypesByName.find(name));
	}

	void addClass(MetaClassBase* pMetaClassBase)
	{
		mTypesByName.insert(pMetaClassBase->mByNameTreeNode);
		mTypesByTypeInfo.insert(pMetaClassBase->mByTypeInfoTreeNode);
	}

	MetaClassBase* findClass(const CStr& name) {
		MetaType* pMetaType = findType(name);
		return downCast<MetaClassBase*>(pMetaType);
	}

	template<typename T>
	MetaClass<T>* findClass() {
		return downCast<MetaClass<T>*>(findType(typeid(T)));
	}

	template<typename T>
	MetaEnum<T>* findEnum() {
		return downCast<MetaEnum<T>*>(findType(typeid(T)));
	}

	static CStrArg getMetaTypeName(MetaType*const & pMetaType) {
		return pMetaType->getName();
	}

	static const std::type_info& getMetaTypeInfo(MetaType*const& pMetaType) {
		return pMetaType->getTypeInfo();
	}

private:

	RbTree<MetaType*, CStr, Meta::getMetaTypeName> mTypesByName;
	RbTree<MetaType*, std::type_info, Meta::getMetaTypeInfo> mTypesByTypeInfo;

	static Meta sSingleton;
};
