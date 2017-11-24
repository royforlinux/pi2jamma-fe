#pragma once


#define META_PRIMITIVE(Type) \
	static MetaPrimitive<Type> gMetaPrimitive##Type(#Type)

#define META_PRIMITIVE2(Type1,Type2) \
	static MetaPrimitive<Type1 Type2> gMetaPrimitive##Type1##Type2(#Type1 " " #Type2)	

#define META_PRIMITIVE3(Type1,Type2,Type3) \
	static MetaPrimitive<Type1 Type2 Type3> gMetaPrimitive##Type1##Type2##Type3(#Type1 " " #Type2 " " #Type3)

class MetaPrimitiveBase :public MetaType
{
public:
	MetaPrimitiveBase(CStrArg name) :
		MetaType(name)
	{}
};

template<typename T>
class MetaPrimitive final : public MetaPrimitiveBase
{
public:
	MetaPrimitive(CStrArg name)
		: MetaPrimitiveBase(name) {

		}

	virtual Result load(void* pItem, const Json& refJson) {
		return Serialize<T>(*static_cast<T>(pItem), refJson);
	}

	virtual const std::type_info& getTypeInfo() const {
		return typeid(T);
	}
};
