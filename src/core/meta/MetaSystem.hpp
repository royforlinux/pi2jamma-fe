#pragma once

#include "core/meta/MetaType.hpp"
#include "core/CString.hpp"
#include "core/container/RbTree.hpp"

#include <typeinfo>
#include <typeindex>

class MetaClassBase;
template<typename T> class MetaClass;
template<typename T> class MetaEnum;

class Meta
{
public:

	static void initialize();

	static Meta& get();

	Meta();

	MetaType* findType(const std::type_info& typeInfo);
	MetaType* findType(CStrArg name);

	template<typename T>
	MetaType* findType() {
		return findType(typeid(T));
	}

	template<typename T>
	Result findType(MetaType*& pMetaType) {
		(pMetaType) = findType<T>();
		if(nullptr ==pMetaType) {
			return
				Result::makeFailureWithString(
					formatString(
						"Type not registered with meta stystem: %x",
						typeid(T).name()));
		}

		return Result::makeSuccess();
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

	void addType(const MetaType& metaType);
	void removeType(const MetaType& metaType);

private:

	RbTree<
		MetaType,
		CStr,
		KeyFinderGetter<MetaType, CStr, & MetaType::getName>,
		NodeFinderField<MetaType, & MetaType::mByNameTreeNode>> mTypesByName;

	RbTree<
		MetaType,
		std::type_info,
		KeyFinderGetter<MetaType, std::type_info, & MetaType::getTypeInfo>,
		NodeFinderField<MetaType, & MetaType::mByTypeInfoTreeNode>> mTypesByTypeInfo;

	static Meta* spSingleton;
};

inline Meta& Meta::get() {
	ASSERT(nullptr != spSingleton);
	return *spSingleton;
}
