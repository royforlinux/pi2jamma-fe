#pragma once

#include "core/meta/MetaType.hpp"
#include "core/cast.hpp"

#define META_CLASS(C) \
	static MetaClass<C> gMetaClass##C(#C)

#if 0
#define META_CLASS_PROPERTY(C, P) \
	static MetaClassProperty<C,decltype(C::m##P)> gMetaClassProperty##C##P( \
		& gMetaClass##C, \
		Meta::get().findType<decltype(C::m##P)>(), \
		#P, \
		[](C* pC, typename Arg<decltype(C::m##P)>::Type v) {pC->m##P = v; }, \
		[](C* pC) -> typename Arg<decltype(C::m##P)>::Type { return pC->m##P; } )
#endif

#define META_CLASS_PROPERTYGS(C, Type, P) \
	static MetaClassProperty<C,Type> gMetaClassProperty##C##P( \
		& gMetaClass##C, \
		Meta::get().findType<decltype(C::m##P)>(), \
		#P, \
		& C::set##P, \
		& C::get##P)

class MetaClassBase;
template<typename T > class MetaClass;

class MetaClassPropertyBase
{
public:
	MetaClassPropertyBase(
		MetaClassBase* pMetaClassBase,
		MetaType* pPropertyType,
		CStrArg name );


	CStrArg getName() const {
		return mName;
	}

	virtual Result load(void* object, const ref<Json>& refJson) = 0;

private:

	CStr mName;
	MetaType* mpPropertyType;

public:
	RbTreeNode<MetaClassPropertyBase*> mTreeNode;
};

template<typename ClassType, typename PropertyType>
class MetaClassProperty : public MetaClassPropertyBase
{
public:

	using Setter = void(ClassType::*)(typename Arg<PropertyType>::Type);
	using Getter = typename Arg<PropertyType>::Type (ClassType::*)(void) const;

	MetaClassProperty(
			MetaClass<ClassType>* pClass,
			MetaType* pPropertyType,
			CStrArg name,
			Setter setter,
			Getter getter)
		: MetaClassPropertyBase(
			pClass,
			pPropertyType,
			name)
		, mSetter(std::move(setter))
		, mGetter(std::move(getter)) {
	}

	virtual Result load(void* object, const ref<Json>& refJson) override
	{
		return Result::makeFailureNotImplemented();
	}

private:

	Setter mSetter;
	Getter mGetter;
};


class MetaClassBase : public MetaType
{
public:

	MetaClassBase(CStrArg name);

	MetaClassPropertyBase* findProperty(CStrArg name) {
		return safeDeRef(mProperties.find(name));
	}

	void addProperty(MetaClassPropertyBase* pMetaClassPropertyBase) {
		mProperties.insert(pMetaClassPropertyBase->mTreeNode);
	}

	Result load(void* object, const ref<Json>& refJson);

private:

	static CStrArg getPropertyName(const MetaClassPropertyBase* pMetaClassProperty) {
		return pMetaClassProperty->getName();
	}

	RbTree<MetaClassPropertyBase*, CStr, getPropertyName> mProperties;
};

template<typename T>
class MetaClass final : public MetaClassBase
{
public:
	MetaClass(CStrArg name)
		: MetaClassBase(name)
	{}

	template<typename P>
	void addProperty(
		const char* pName,
		typename MetaClassProperty<T,P>::Setter setter,
		typename MetaClassProperty<T,P>::Getter getter) {

		make_ref<MetaClassProperty<T,P>>(
			pName,
			std::move(setter),
			std::move(getter));
	}

private:

	virtual const std::type_info& getTypeInfo() const override {
		return typeid(T);
	}
};

