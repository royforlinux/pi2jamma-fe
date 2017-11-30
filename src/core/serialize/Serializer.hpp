#pragma once

#include "core/meta/MetaSystem.hpp"
#include "core/serialize/ObjectWriteStream.hpp"
#include "core/serialize/ObjectReadStream.hpp"

template<typename T >
struct Serializer
{
	static Result load(T& object, ObjectReadStream& readStream) {
		MetaType* pType = nullptr;
		Result r = Meta::get().findType<T>(pType);
		if( r.peekFailed()) {
			return r;
		}

		return pType->load(&object, readStream);
	}

	static Result save(const T& object, ObjectWriteStream& writeStream) {
		MetaType* pType = nullptr;
		Result r = Meta::get().findType<T>(pType);
		if(r.peekFailed()) {
			return r;
		}
		
		return pType->save(&object, writeStream);
	}
};

template<typename T>
Result load(T& t, ObjectReadStream& readStream) {
	return Serializer<T>::load(t,readStream);
}

template<typename T>
Result load(T& t, CStr fileName)
{
	ASSERT(false);
	return Result::makeFailureNotImplemented();
	#if 0
	Json json;

	Result result = JsonLoadFromFile(json, fileName.c_str());
	if(result.peekFailed()) {
		return result;
	}

	return load(t, json);
	#endif
};

template<typename T>
Result save(const T& t, ObjectWriteStream& writeStream) {
	return Serializer<T>::save(t, writeStream);
}

template<typename T>
struct SerializerInt
{
	static Result load(T& object, ObjectReadStream& readStream) {
		return readStream.readInteger(object);
	}

	static Result save(T object, ObjectWriteStream& writeStream) {
		return writeStream.writeInteger(object);
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
	static Result load(T& object, ObjectReadStream& readStream) {
		return readStream.readFloat(object);
	}

	static Result save(T object, ObjectWriteStream& writeStream) {
		return writeStream.writeFloat(object);
	}	
};

template<> struct Serializer<float> : public SerializerFloat<float> {};
template<> struct Serializer<double> : public SerializerFloat<double>{};

template<>
struct Serializer<bool>
{
	static Result load(bool& object, ObjectReadStream& readStream) {
		return readStream.readBoolean(object);
	}

	static Result save(bool object, ObjectWriteStream& writeStream) {
		return writeStream.writeBoolean(object);
	}	
};


