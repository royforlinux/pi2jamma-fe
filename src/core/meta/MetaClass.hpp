#pragma once

#include "core/meta/MetaType.hpp"
#include "core/cast.hpp"

#define META_CLASS(C) \
	MetaClass<C> gMetaClass##C(#C)

#define META_PROPERTY(C, P) \
	MetaClassProperty<C,decltype(C::m##P)> gMetaClassProperty##C##P( \
		& gMetaClass##C, \
		#P, \
		[](C* pC, const decltype(C::m##P)& v) {pC->m##P = v; }, \
		[](C* pC) -> const decltype(C::m##P)& { return pC->m##P; } )

class MetaClassBase;
template<typename T > class MetaClass;

class MetaClassPropertyBase
{
public:
	MetaClassPropertyBase(
		MetaClassBase* pMetaClassBase,
		const CStrArg name );


	CStrArg getName() const {
		return mName;
	}

private:

	CStr mName;

public:
	RbTreeNode<MetaClassPropertyBase*> mTreeNode;
};

template<typename ClassType, typename PropertyType>
class MetaClassProperty : public MetaClassPropertyBase
{
public:

	using Setter = std::function<void(ClassType*, const PropertyType&)>;
	using Getter = std::function<const PropertyType&(ClassType*)>;

	MetaClassProperty(
			MetaClass<ClassType>* pClass,
			CStrArg name,
			Setter setter,
			Getter getter)
		: MetaClassPropertyBase(
			pClass,
			name)
		, mSetter(std::move(setter))
		, mGetter(std::move(getter)) {
	}

private:

	Setter mSetter;
	Getter mGetter;
};


class MetaClassBase : public MetaType
{
public:

	MetaClassBase(CStrArg name)
		: MetaType(name) {

	}

	MetaClassPropertyBase* findProperty(CStrArg name) {
		return safeDeRef(mProperties.find(name));
	}

	void addProperty(MetaClassPropertyBase* pMetaClassPropertyBase) {
		mProperties.insert(pMetaClassPropertyBase->mTreeNode);
	}

	virtual Result load(LoadTextContext& loadTextContext) override;

private:

	static CStrArg getPropertyName(MetaClassPropertyBase*const& pMetaClassProperty) {
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