#pragma once

class ObjectWriteStream
{
public:
	virtual ~ObjectWriteStream() = default;

	virtual Result writeNativeFloat(double flt) = 0;
	virtual Result writeNativeInt(uint64_t i) = 0;
	virtual Result writeBoolean(bool b) = 0;
	virtual Result writeCVariableName(CStr c) = 0;

	virtual Result beginObject() = 0;
	virtual Result beginField(CStr name) = 0;
	virtual Result endField() = 0;
	virtual Result endObject() = 0;
	virtual Result beginArray() = 0;
	virtual Result endArray() = 0;
	
	template<typename T>
	Result writeFloat(T t) {
		return writeNativeFloat(static_cast<double>(t));
	}

	template<typename T>
	Result writeInteger(T t) {
		return writeNativeInt(static_cast<uint64_t>(t));
	}
};