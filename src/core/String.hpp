#pragma once

#include <memory.h>
#include "core/Arg.hpp"

class CStr
{
public:

	CStr(const char* pStr)
		: mpStr(pStr) {
	}

	bool operator==(const CStr& rhs) const {
		return strcmp(mpStr, rhs.mpStr) == 0;
	}

private:

	const char* mpStr;
};

template<>
struct Arg<CStr>
{
	using Type = CStr;
};

using CStrArg = Arg<CStr>::Type;