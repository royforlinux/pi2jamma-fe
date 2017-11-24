#pragma once

class MetaPrimitiveBase final :public MetaType
{
public:
	MetaPrimitiveBase(CStrArg name) :
		MetaType(name)
	{}
};

template<typaname T>
class MetaPrimative : public MetaPrimitiveBase
{
public:
	MetaPrimitive(CStrArg name)
		: metaPrimitiveBase(name) {

		}

	virtual Result load(void* pItem, const ref<Json>& refJson) {
		return Result::makeFailureNotImplemented();
	}

	virtual const std::type_info& getTypeInfo() const {
		return typeid(T);
	}
}
