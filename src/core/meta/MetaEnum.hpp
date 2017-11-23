#pragma once

#include "core/meta/MetaType.hpp"
#include <memory>
#include <unordered_map>

#define META_ENUM(E) \
	MetaEnum<E> gMetaEnum##E(#E)

#define META_ENUM_VALUE(E, V) \
	MetaEnumValue<E> gMetaEnumValue##E##V(&gMetaEnum##E, #V, E::V)

class MetaEnumBase;
template<typename T> class MetaEnum;

class MetaEnumValueBase
{
public:
	MetaEnumValueBase(
		MetaEnumBase* pMetaEnumBase,
		CStrArg name)
		: mName(name)
	{}

	Arg<CStr>::Type getName() const {
		return mName;
	}


private:
	CStr mName;
};

template<typename T>
class MetaEnumValue final : public MetaEnumValueBase
{
	public:
		MetaEnumValue(
			MetaEnum<T>* pEnum,
			CStrArg name,
			T value)
			: MetaEnumValueBase(
				pEnum,
				name)
			, mValue(value)
		{}

	private:

		T mValue;

};

class MetaEnumBase : public MetaType
{
public:
	MetaEnumBase(const char* pName, size_t numBytes)
		: MetaType(pName)
		, mNumBytes(numBytes)
	{
	}

	virtual Result load(LoadTextContext& loadTextContext) override { return Result::makeFailureNotImplemented(); }

private:

	size_t mNumBytes;

	std::unordered_map<size_t, std::unique_ptr<MetaEnumBase>> mValues;
};

template<typename T>
class MetaEnum final : public MetaEnumBase
{
public:
	MetaEnum(const char* pName)
		: MetaEnumBase(pName, sizeof(T))
	{}

	void addValue(const char* pName, T v) {
		make_ref<MetaEnumValue<T>>(pName, v);
	}
private:

	virtual const std::type_info& getTypeInfo() const override { return typeid(T); }	
};