#include "core/meta/MetaEnum.hpp"

#include "core/meta/Meta.hpp"

MetaEnumBase::MetaEnumBase(CStrArg name, size_t numBytes)
	: MetaType(name)
	, mNumBytes(numBytes)
{
}


