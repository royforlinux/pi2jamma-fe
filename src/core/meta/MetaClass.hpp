#pragma once

#include "core/meta/MetaType.hpp"

#include "core/cast.hpp"
#include "core/serialize/Serializer.hpp"

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
	virtual ~MetaClassProperty();


	CStrArg getName() const {
		return mName;
	}

	MetaType* getType() const {
		return mpPropertyType;
	}

	virtual Result load(void* pVoidObject, const Json& json) const= 0;
	virtual Result save(const void* pVoidObject, Json& json) const = 0;

private:

	CStr mName;
	MetaType* mpPropertyType;
	MetaClassBase* mpMetaClassBase;

public:
	RbTreeNode mTreeNode;
};

template<typename ClassType, typename PropertyType>
class MetaClassPropertyBase : public MetaClassProperty
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

	virtual Result load(void* pVoidObject, const Json& json) const override
	{
		ClassType* pObject = static_cast<ClassType*>(pVoidObject);

		PropertyType& prop = pObject->*mMember;

		return Serializer<PropertyType>::load(prop, json);
	}

	virtual Result save(const void* pVoidObject, Json& json) const override {
		const ClassType* pObject = static_cast<const ClassType*>(pVoidObject);
		const PropertyType& prop = pObject->*mMember;

		return Serializer<PropertyType>::save(prop, json);
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

	virtual Result load(void* pVoidObject, const Json& json) const override
	{
		DecayType value;

		Result result = Serializer<DecayType>::load(value, json);
		if(result.peekFailed()) {
			return result;
		}

		ClassType* pObject = static_cast<ClassType*>(pVoidObject);
		(pObject->*mSetter)(std::move(value));

		return Result::makeSuccess();
	}

	virtual Result save(const void* pVoidObject, Json& json) const override {
		const ClassType* pObject = static_cast<const ClassType*>(pVoidObject);		
		return Serializer<DecayType>::save((pObject->*mGetter)(), json);
	}

private:

	Setter mSetter;
	Getter mGetter;
};


class MetaClassBase : public MetaType
{
public:

	MetaClassBase(CStrArg name, const std::type_info& typeInfo);

	MetaClassProperty* findProperty(CStrArg name) {
		return mProperties.find(name);
	}

	void addProperty(MetaClassProperty* pMetaClassProperty) {
		mProperties.insert(*pMetaClassProperty);
	}

	void removeProperty(MetaClassProperty* pMetaClassProperty) {
		mProperties.remove(*pMetaClassProperty);
	}

	virtual Result load(void* pVoidObject, const Json& refJson) const override;

	virtual Result save(const void* pVoidObject, Json& json) const override;


private:

	static CStrArg getPropertyName(const MetaClassProperty& prop) {
		return prop.getName();
	}

	RbTree<
		MetaClassProperty,
		CStr,
		KeyFinderGetter<MetaClassProperty, CStr, & MetaClassProperty::getName>,
		NodeFinderField<MetaClassProperty, &MetaClassProperty::mTreeNode>> mProperties;
};

template<typename T>
class MetaClass final : public MetaClassBase
{
public:
	MetaClass(CStrArg name)
		: MetaClassBase(name, typeid(T))
	{}
};

