#include "core/meta/MetaEnum.hpp"

#include "core/meta/Meta.hpp"

MetaEnumBase::MetaEnumBase(CStrArg name, size_t numBytes, const std::type_info& typeInfo)
	: MetaType(name, typeInfo)
	, mNumBytes(numBytes)
{
}


