#pragma once

#include "core/meta/MetaEnum.hpp"
#include "core/meta/MetaClass.hpp"

#include <unordered_map>
#include <typeinfo>
#include <typeindex>

class Meta
{
public:

	static Meta& get() {
		static Meta singleton;
		return singleton; }

	Meta();

	MetaType* findType(const std::type_info& typeInfo) {
		return safeDeRef(mTypesByTypeInfo.find(typeInfo));
	}

	MetaType* findType(CStrArg name) {
		return safeDeRef(mTypesByName.find(name));
	}

	template<typename T>
	MetaType* findType() {
		return findType(typeid(T));
	}

	MetaClassBase* findClass(CStrArg name) {
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

	template<typename T>
	Result load(T& item, const ref<Json>& refJson) {
		MetaType* pType = findType<T>();
		if(nullptr == pType) {
			return Result::makeFailureWithStringLiteral("No such type");
		}

		return pType->load(&item, refJson);
	}

	static CStrArg getMetaTypeName(const MetaType* pMetaType) {
		return pMetaType->getName();
	}

	static const std::type_info& getMetaTypeInfo(const MetaType* pMetaType) {
		return pMetaType->getTypeInfo();
	}

	void addType(MetaType* pMetaType)
	{
		mTypesByName.insert(pMetaType->mByNameTreeNode);
		mTypesByTypeInfo.insert(pMetaType->mByTypeInfoTreeNode);
	}

private:

	RbTree<MetaType*, CStr, Meta::getMetaTypeName> mTypesByName;
	RbTree<MetaType*, std::type_info, Meta::getMetaTypeInfo> mTypesByTypeInfo;
};
