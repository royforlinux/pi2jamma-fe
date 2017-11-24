#pragma once

#include "core/meta/MetaType.hpp"
#include "core/cast.hpp"

#define META_CLASS(C) \
	static MetaClass<C> gMetaClass##C(#C)


#define META_CLASS_FIELD(C, P) \
	static MetaClassField<C,decltype(C::m##P)> gMetaClassField##C##P( \
		Meta::get().findClass<C>(), \
		Meta::get().findType<decltype(C::m##P)>(), \
		#P, \
		& C::m##P )


#define META_CLASS_PROPERTY(C, P) \
	using MetaClassGetSet##C##PType = decltype(std::declval<C>().get##P()); \
	using MetaClassGetSet##C##PDecayType = std::decay<MetaClassGetSet##C##PType>::type; \
	static MetaClassGetSet<C,MetaClassGetSet##C##PType,MetaClassGetSet##C##PDecayType> gMetaClassProperty##C##P( \
		Meta::get().findClass<C>(), \
		Meta::get().findType<MetaClassGetSet##C##PDecayType>(), \
		#P, \
		& C::set##P, \
		& C::get##P)

class MetaClassBase;
template<typename T > class MetaClass;

class MetaClassProperty
{
public:
	MetaClassProperty(
		MetaClassBase* pMetaClassBase,
		MetaType* pPropertyType,
		CStrArg name );


	CStrArg getName() const {
		return mName;
	}

	virtual Result load(void* object, const Json& json) = 0;

private:

	CStr mName;
	MetaType* mpPropertyType;

public:
	RbTreeNode<MetaClassProperty*> mTreeNode;
};

template<typename ClassType, typename PropertyType>
class MetaClassPropertyBase : MetaClassProperty
{
public:
	MetaClassPropertyBase(
		MetaClass<ClassType>* pClassType,
		MetaType* pPropertyType,
		CStrArg name )
		: MetaClassProperty(
			pClassType,
			pPropertyType,
			name)
	{
	}
};
template<typename ClassType, typename PropertyType>
class MetaClassField
	: public MetaClassPropertyBase<ClassType, PropertyType>
{
public:
	using Member = PropertyType(ClassType::*);

	MetaClassField(
		MetaClass<ClassType>* pClass,
		MetaType* pPropertyType,
		CStrArg name,
		Member member)		
		: MetaClassPropertyBase<ClassType,PropertyType>(
			pClass,
			pPropertyType,
			name)
		, mMember(member)
		{

		}

	virtual Result load(void* object, const Json& refJson) override
	{
		return Result::makeFailureNotImplemented();
	}

private:

	Member mMember;
};

template<typename ClassType, typename ParamType, typename DecayType>
class MetaClassGetSet
	: public MetaClassPropertyBase<ClassType,DecayType>
{
public:

	using Setter = void(ClassType::*)(ParamType);
	using Getter = ParamType (ClassType::*)(void) const;

	MetaClassGetSet(
		MetaClass<ClassType>* pClass,
		MetaType* pPropertyType,
		CStrArg name,
		Setter setter,
		Getter getter)
		: MetaClassPropertyBase<ClassType,DecayType>(
		pClass,
		pPropertyType,
		name)
		, mSetter(std::move(setter))
		, mGetter(std::move(getter)) {
	}

	virtual Result load(void* object, const Json& json) override
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

	MetaClassProperty* findProperty(CStrArg name) {
		return safeDeRef(mProperties.find(name));
	}

	void addProperty(MetaClassProperty* pMetaClassProperty) {
		mProperties.insert(pMetaClassProperty->mTreeNode);
	}

	Result load(void* object, const Json& refJson);

private:

	static CStrArg getPropertyName(const MetaClassProperty* pMetaClassProperty) {
		return pMetaClassProperty->getName();
	}

	RbTree<MetaClassProperty*, CStr, getPropertyName> mProperties;
};

template<typename T>
class MetaClass final : public MetaClassBase
{
public:
	MetaClass(CStrArg name)
		: MetaClassBase(name)
	{}

private:

	virtual const std::type_info& getTypeInfo() const override {
		return typeid(T);
	}
};

