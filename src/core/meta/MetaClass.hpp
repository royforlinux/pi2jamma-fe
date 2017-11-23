#pragma once

#include "core/meta/MetaType.hpp"

#define META_CLASS(C) \
	Meta::get().addClass<C>(#C)

#define META_PROPERTY(C, P) \
	Meta::get().findClass<C>()->addProperty<decltype(m##P)>( \
		[](C* pC, const decltype(C::m##P)& v) {pC->m##P = v; }, \
		[](C* pC) { return pC->m##P; })

class MetaClassPropertyBase : public RefCounted
{
public:
	MetaClassPropertyBase(const char* pName )
		: mpName(pName) {
	}

	const char* getName() const {
		return mpName;
	}

private:
	const char* mpName;
};

template<typename ClassType, typename PropertyType>
class MetaClassProperty : MetaClassPropertyBase
{
public:

	using Setter = std::function<void(ClassType*, const PropertyType&)>;
	using Getter = std::function<const PropertyType&(ClassType*)>;

	MetaClassProperty(const char* pName, Setter setter, Getter getter)
		: MetaClassPropertyBase(pName)
		, mSetter(std::move(setter))
		, mGetter(std::Mmve(getter)) {
	}
};


class MetaClassBase : public MetaType
{
public:

	MetaClassBase(const char* pName)
		: MetaType(pName) {

	}
};

template<typename T>
class MetaClass final : public MetaClassBase
{
public:
	MetaClass(const char* pName)
		: MetaClassBase(pName)
	{}

	template<typename P>
	void addProperty(
		const char* pName,
		typename MetaPropertyBase<T,P>::Setter setter,
		typename MetaPropertyBase<T,P>::Getter getter) {
		auto hash = std::hash
		mProperties.insert(std::make_pair
	}

	std::unordered_map<size_t, ref<MetaClassPropertyBase> mProperties;
};