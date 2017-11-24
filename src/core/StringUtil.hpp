#pragma once

#include "core/Arg.hpp"
#include "core/String.hpp"

#include "debug.hpp"
#include <memory.h>
#include <typeinfo>
#include <string>

#define SL(x) x
#define TS(x) x
#define FS(fmt, ...) string_format(fmt, __VA_ARGS__)

inline std::string string_format(const char* fmt, ...)
{
	ASSERT(false);
	return std::string();
}

inline String indent( size_t spaces )
{
    String s;
    
    for( size_t i = 0; i < spaces; i ++ )
    {
        s += Sl("    ");
    }
    
    return s;
}

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

struct OmStringEscapeItem
{
    const char* mpSequenceToEscape;
    const char* mpEscapeSequence;
};

struct OmStringEscapeItems
{
    OmStringEscapeItem* mpItems;
    size_t mNumItems;
};

extern OmStringEscapeItems OM_STRING_C_ESCAPE_ITEMS;

const String OmStringEscape(
    Arg< String >::Type s,
    Arg< OmStringEscapeItems >::Type escapeItems = OM_STRING_C_ESCAPE_ITEMS );