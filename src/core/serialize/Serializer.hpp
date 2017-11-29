#pragma once

#include "core/json/JsonParser.hpp"
#include "core/meta/MetaSystem.hpp"

template<typename T >
struct Serializer
{
	static Result load(T& object, const Json& json) {
		MetaType* pType = nullptr;
		Result r = Meta::get().findType<T>(pType);
		if( r.peekFailed()) {
			return r;
		}

		return pType->load(&object, json);
	}

	static Result save(const T& object, Json& json) {
		MetaType* pType = nullptr;
		Result r = Meta::get().findType<T>(pType);
		if(r.peekFailed()) {
			return r;
		}
		
		return pType->save(&object, json);
	}
};

template<typename T>
Result load(T& t, const Json& json) {
	return Serializer<T>::load(t,json);
}

template<typename T>
Result load(T& t, CStr fileName)
{
	Json json;

	Result result = JsonLoadFromFile(json, fileName.c_str());
	if(result.peekFailed()) {
		return result;
	}

	return load(t, json);
};

template<typename T>
Result save(const T& t, Json& json) {
	return Serializer<T>::save(t, json);
}

template<typename T>
struct SerializerInt
{
	static Result load(T& object, const Json& json) {
		if(json.GetType() != JsonBase::Type::Integer) {
			return Result::makeFailureWithStringLiteral("Not an ingeger");
		}

		object = json.GetInteger<T>();
		LogFmt("Load Int %d\n", int(object) );

		return Result::makeSuccess();
	}

	static Result save(const T& object, Json& json) {
		LogFmt("Save Int %d\n", int(object) );
		json = Json(object);
		return Result::makeSuccess();

	}
};

template<> struct Serializer<char> : public SerializerInt<char> {};
template<> struct Serializer<unsigned char> : public SerializerInt<unsigned char> {};
template<> struct Serializer<short> : public SerializerInt<short> {};
template<> struct Serializer<unsigned short> : public SerializerInt<unsigned short> {};
template<> struct Serializer<int> : public SerializerInt<int> {};
template<> struct Serializer<unsigned int> : public SerializerInt<unsigned int>{};
template<> struct Serializer<long> : public SerializerInt<long> {};
template<> struct Serializer<unsigned long> : public SerializerInt<unsigned long>{};

template<typename T>
struct SerializerFloat
{
	static Result load(T& object, const Json& json) {
		if(json.GetType() != JsonBase::Type::Real) {
			return Result::makeFailureWithStringLiteral("Not a float.");
		}

		object = json.GetFloat<T>();

		return Result::makeSuccess();
	}

	static Result save(const T& object, Json& json) {
		json = Json(object);
		return Result::makeSuccess();

	}	
};

template<> struct Serializer<float> : public SerializerFloat<float> {};
template<> struct Serializer<double> : public SerializerFloat<double>{};

template<>
struct Serializer<bool>
{
	static Result load(bool& object, const Json& json) {
		if(!json.IsBool()) {
			return Result::makeFailureWithStringLiteral("Not a bool");
		}

		object = json.GetBool();

		return Result::makeSuccess();
	}

	static Result save(bool object, Json& json) {
		json = Json(object);
		return Result::makeSuccess();

	}	
};


