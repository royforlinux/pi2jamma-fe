#pragma once

#include "core/container/RbTree.hpp"

class Json;
class JsonClass;

class Json : public RefCounted
{
public:

	using FloatType = double;
	using IntType = int64_t;
	using ArrayType = std::vector<ref<Json>>;

	enum class Type {
		Class,
		Array,
		Int,
		Float,
		String
	};

	Json(Type t )
		: mType(t) {
	}

	virtual ~Json() = default;	

	Type getType() const {
		return mType;
	}

	static Result asClass(ref<JsonClass>& refClass, const ref<Json>& refJson);

private:

	Type mType;
};

class JsonClassMember
{
public:
	JsonClassMember(
		std::string name,
		ref<Json> value)
		: mName(std::move(name))
		, mrefValue(std::move(value))
		, mTreeNode(this)
	{}
	
	const std::string& getName() const {
		return mName;
	}

	const ref<Json> getValue() const {
		return mrefValue;
	}

	std::string mName;
	ref<Json> mrefValue;
	RbTreeNode<JsonClassMember*> mTreeNode;
};

class JsonClass final : public Json
{
public:
	JsonClass()
		: Json(Type::Class) {
	}

	void setMember(std::string name, ref<Json> refValue) {
		JsonClassMember* pMember =
			new JsonClassMember(name, std::move(refValue));

		mMembers.insert(pMember->mTreeNode);
	}

	ref<Json> getMember(CStrArg name) {
		JsonClassMember* pMember = safeDeRef(mMembers.find(name.c_str()));
		if(nullptr==pMember) {
			return nullptr;
		}
		return pMember->getValue();
	}

	static const std::string& getMemberName( const JsonClassMember* pMember) {
		return pMember->getName();
	} 
private:
	
	RbTree<
		JsonClassMember*,
		std::string,
		getMemberName,
		DeleteLifetimePolicy<JsonClassMember*>> mMembers;
	
};

class JsonInt : public Json
{
public:

	JsonInt(IntType value)
		: Json(Type::Int)
		, mValue(value)
	{}

private:

	IntType mValue;
};

class JsonFloat: public Json
{
public:
	
	JsonFloat(FloatType v)
		: Json(Type::Float)
		, mValue(v)
	{}
private:
	FloatType mValue;
};

class JsonString : public Json
{
public:
	JsonString(std::string s)
		: Json(Type::String)
		, mString(std::move(s)) {
	}
private:
	std::string mString;
};



class JsonArray : public Json
{
	public:
		using ArrayType = std::vector<ref<Json>>;

		JsonArray()
			: Json(Type::Array)
		{}

		const ArrayType& get() {
			return mValues;
		}

	private:

		ArrayType mValues;
};

inline Result Json::asClass(ref<JsonClass>& refClass, const ref<Json>& refJson) {
	if(refJson.isNull()) {
		return Result::makeFailureWithStringLiteral("null is not a class.");
	}

	if(refJson->getType() != Type::Class) {
		return Result::makeFailureWithStringLiteral("not null but not a class.");
	}

	refClass = refJson.downCast<JsonClass>();

	return Result::makeSuccess();
}
