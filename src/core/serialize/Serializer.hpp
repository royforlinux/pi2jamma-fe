#pragma once

template<typename T >
struct Serializer
{
	Result load(T& object, const Json& json) {
		MetaType* pType = Meta::get().findType<T>();
		return pType->load(&t, json);
	}

}

template<typename T >
Result loadText<T& t, const Json& json) {
	return Serializer<T>::load(t,json);
}

template<typename T>
struct SerializerInt
{
	Result load(T& object, const Json& json) {
		if(json.GetType() != JsonBase::Type::Integer) {
			return Result::makeFailureWithStringLiteral("Not an ingeger");
		}

		object = static_cast<T>(json.GetInteger());

		return Result::make::success();
	}
}

template<> struct Serializer<char> : public SerializerInt<char> {}
template<> struct Serializer<unsigned char> : public SerializerInt<unsigned char> {}
template<> struct Serialzier<short> : public SerializerInt<short> {}
template<> struct Serialzier<unsigned short> : public SerializerInt<short> {}
template<> struct Serializer<int> : public SerializerInt<int> {}
template<> struct Serializer<unsigned int> : public SerialializerInt<unsigned int>{}
template<> struct Serializer<long> : public SerializerInt<long> {}
template<> struct Serializer<unsigned long> : public SerializerInt<unsigned long>{}


