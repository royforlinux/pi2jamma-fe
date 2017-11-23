#pragma once

#include "core/meta/MetaEnum.hpp"
#include "core/meta/MetaClass.hpp"

#include <unordered_map>
#include <typeinfo>
#include <typeindex>

#define META_ADD_ENUM(E) \
	Meta::get().addEnum<E>(#E)

#define META_ADD_VALUE(pE, V) \
	pE->addValue(#V, V)

class Meta
{
public:

	static Meta& get() { return sSingleton; }

	template<typename T>
	MetaEnum<T>* addEnum(const char* pName)
	{
		auto e = make_ref<MetaEnum<T>>(pName);

		auto nameHash = std::hash<const char*>()(pName);
		auto pair = std::make_pair(nameHash, e);

		mTypes.insert(pair);
		mTypesByTypeId.insert(std::make_pair(std::type_index(typeid(T)), e));
		mEnums.insert(pair);

		return e.get();
	}

	template<typename T>
	MetaClass<T>* addClass(const char* pName)
	{
		auto c = make_ref<MetaClass<T>>(pName);

		auto nameHash = std::hash<const char*>()(pName);
		auto pair = std::make_pair(nameHash, c);

		mTypes.insert(pair);
		mTypesByTypeId.insert(std::make_pair(std::type_index(typeid(T)), c));
		mClasses.insert(pair);

		return c.get();
	}

	template<typename T>
	MetaClass<T>* findClass() {
		auto iter = mTypesByTypeId.find(std::type_index(typeid(T)));
		
		if(iter == mTypesByTypeId.end()) {
			return nullptr;
		}

		return static_cast<MetaClass<T>*>((*iter).second.get());
	}


private:

	std::unordered_map<size_t, ref<MetaType>> mTypes;
	std::unordered_map<std::type_index, ref<MetaType>> mTypesByTypeId;
	std::unordered_map<size_t, ref<MetaEnumBase>> mEnums;
	std::unordered_map<size_t, ref<MetaClassBase>> mClasses;

	static Meta sSingleton;
};
