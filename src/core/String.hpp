#pragma once

#include "core/Arg.hpp"
#include <memory.h>
#include <typeinfo>

class CStr
{
public:

	CStr(const char* pStr)
		: mpStr(pStr) {
	}

	bool operator==(const CStr& rhs) const {
		LogFmt("s1:%s s2:%s\n", mpStr, rhs.mpStr);
		return strcmp(mpStr, rhs.mpStr) == 0;
	}

	const char* c_str() const { return mpStr; }

private:

	const char* mpStr;
};

template<>
struct Arg<CStr>
{
	using Type = CStr;
};

using CStrArg = Arg<CStr>::Type;

namespace std
{
	inline std::string to_string(CStrArg s) {
		return s.c_str();
	}

	inline std::string to_string(const std::type_info& ti) {
		return ti.name();
	}

	inline const std::string& to_string(const std::string& s) {
		return s;
	}
}