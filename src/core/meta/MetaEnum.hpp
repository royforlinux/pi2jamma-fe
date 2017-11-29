#pragma once

#include "core/meta/MetaType.hpp"
#include <memory>
#include <unordered_map>

#define META_ENUM(E) \
	static MetaEnum<E> gMetaEnum##E(#E)

#define META_ENUM_VALUE(E, V) \
	static MetaEnumValue<E> gMetaEnumValue##E##V(Meta::get().findEnum<E>(), #V, E::V)

class MetaEnumBase;
template<typename T> class MetaEnum;

class MetaEnumValueBase
{
public:
	MetaEnumValueBase(
		MetaEnumBase* pMetaEnumBase,
		CStrArg name)
		: mName(name)
		, mNameTreeNode(this)
		, mValueTreeNode(this)
	{}

	Arg<CStr>::Type getName() const {
		return mName;
	}

	virtual uint64_t getValue() const = 0;

private:
	CStr mName;

public:
	RbTreeNode<MetaEnumValueBase*> mNameTreeNode;
	RbTreeNode<MetaEnumValueBase*> mValueTreeNode;
};

template<typename T>
class MetaEnumValue final : public MetaEnumValueBase
{
	public:
		MetaEnumValue(
			MetaEnum<T>* pEnum,
			CStrArg name,
			T value);

	virtual uint64_t getValue() const override {
		return static_cast<uint64_t>(mValue);
	}		

	T getTypedValue() const {
		return mValue;
	}	

	private:

		T mValue;

};

class MetaEnumBase : public MetaType
{
public:
	MetaEnumBase(CStrArg name, size_t numBytes, const std::type_info& typeInfo);

	void addValue(MetaEnumValueBase* pValue) {
		mValuesByName.insert(pValue->mNameTreeNode);
		mValuesByValue.insert(pValue->mValueTreeNode);
	}

	const MetaEnumValueBase* findValue(uint64_t value) const {
		return safeDeRef(mValuesByValue.findItem(value));
	}

	Result findValue(const MetaEnumValueBase*& vb, CStr name) const {
		vb = findValue(name);
		if(nullptr == vb) {
			return Result::makeFailureWithString(
				formatString(
					"%s is not a valid %s enum value.",
					name.c_str(),
					getName().c_str()));
		}

		return Result::makeSuccess();
	}

	Result findValue(const MetaEnumValueBase*& vb, uint64_t value) const {
		vb = findValue(value);
		if(nullptr == vb) {
			return Result::makeFailureWithString(
				formatString(
					"%d is not a valid %s enum value.",
					(int) value,
					getName().c_str()));
		}

		return Result::makeSuccess();
	}
	const MetaEnumValueBase* findValue(CStr name) const {
		return safeDeRef(mValuesByName.findItem(name));
	}

private:

	static CStr getValueName(const MetaEnumValueBase* pValue) {
		return pValue->getName();
	}

	static uint64_t getValueValue(const MetaEnumValueBase* pValue) {
		return pValue->getValue();
	}

	size_t mNumBytes;

	RbTree<MetaEnumValueBase*, CStr, getValueName> mValuesByName;
	RbTree<MetaEnumValueBase*, uint64_t, getValueValue > mValuesByValue;
};

template<typename T>
class MetaEnum final : public MetaEnumBase
{
public:
	MetaEnum(const char* pName)
		: MetaEnumBase(pName, sizeof(T), typeid(T))
	{}

	virtual Result load(void* pVoidEnum, const Json& json) const override
	{
		if(!json.IsString()) {
			return Result::makeFailureWithStringLiteral("Expected string for enum value");
		}

		const MetaEnumValueBase* pValueBase = 0;

		Result r = findValue(pValueBase, json.GetString().c_str());

		if(r.peekFailed()) {
			return r;
		}

		const MetaEnumValue<T>* pValue =
			downCast<const MetaEnumValue<T>*>(
				pValueBase);

		T* pT = static_cast<T*>(pVoidEnum);

		(*pT) = static_cast<T>(pValue->getTypedValue());

		return Result::makeSuccess();
	}

	virtual Result save(const void* pVoidEnum, Json& json) const override
	{
		const T* pEnum = static_cast<const T*>(pVoidEnum);

		const MetaEnumValueBase* pValueBase = nullptr;

		Result r = findValue(pValueBase, static_cast<uint64_t>(*pEnum));
		if(r.peekFailed()) {
			return r;
		}

		json = Json(pValueBase->getName().c_str());

		return Result::makeSuccess();
	}
};

template<typename T>
MetaEnumValue<T>::MetaEnumValue(
	MetaEnum<T>* pEnum,
	CStrArg name,
	T value)
	: MetaEnumValueBase(pEnum, name)
	, mValue(value)
{
	ASSERT(nullptr != pEnum);
	pEnum->addValue(this);
}