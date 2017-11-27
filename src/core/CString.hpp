#pragma once

#include "core/Arg.hpp"
#include <memory.h>

extern const char* OM_EMPTY_C_STRING;

class CStr
{
public:

    CStr(const char* pStr)
        : mpStr(pStr) {
    }

    bool operator==(const CStr& rhs) const {

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

inline bool EndsWith( const char* pS, const char* pE )
{
    const char* pRes = strstr( pS, pE );
    
    return pRes == ( pS + strlen( pS ) - strlen( pE ) );
}

void OmCStringDumpHex( const char* pSIn );
