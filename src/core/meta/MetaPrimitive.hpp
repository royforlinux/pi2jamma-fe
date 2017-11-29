#pragma once

#include "core/serialize/Serializer.hpp"

#define META_PRIMITIVE(Type) \
	static MetaPrimitive<Type> gMetaPrimitive##Type(#Type)

#define META_PRIMITIVE2(Type1,Type2) \
	static MetaPrimitive<Type1 Type2> gMetaPrimitive##Type1##Type2(#Type1 " " #Type2)	

#define META_PRIMITIVE3(Type1,Type2,Type3) \
	static MetaPrimitive<Type1 Type2 Type3> gMetaPrimitive##Type1##Type2##Type3(#Type1 " " #Type2 " " #Type3)

class MetaPrimitiveBase :public MetaType
{
public:
	MetaPrimitiveBase(CStrArg name, const std::type_info& typeInfo) :
		MetaType(name, typeInfo)
	{}
};

template<typename T>
class MetaPrimitive final : public MetaPrimitiveBase
{
public:
	MetaPrimitive(CStrArg name)
		: MetaPrimitiveBase(name,typeid(T)) {

		}

	virtual Result load(void* pItem, const Json& json) const override {
		return Serializer<T>::load(*static_cast<T*>(pItem), json);
	}

	virtual Result save(const void* pItem, Json& json) const override {
		return Serializer<T>::save(*static_cast<const T*>(pItem), json);
	}

};
