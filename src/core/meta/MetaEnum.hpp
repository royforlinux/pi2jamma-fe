#pragma once

#include "core/meta/MetaType.hpp"
#include <memory>
#include <unordered_map>

class MetaEnumValueBase 
{
public:
	MetaEnumValueBase(const char* pName)
		: mpName(pName)
	{}

	const char* getName() const {
		return mpName;
	}

private:
	const char* mpName;
};

template<typename T>
class MetaEnumValue final : public MetaEnumValueBase
{
	public:
		MetaEnumValue(const char* pName, T value)
			: MetaEnumValueBase(pName)
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

private:

	size_t mNumBytes;

	std::unordered_map<size_t, std::unique_ptr<MetaEnumBase>> mValues;
};

template<typename T>
class MetaEnum final : public MetaEnumBase
{
public:
	MetaEnum(std::string name)
		: MetaEnumBase(std::move(name), sizeof(T))
	{}
};