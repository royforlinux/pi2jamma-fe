#include "core/StringUtil.hpp"

OmStringEscapeItem OM_STRING_C_ESCAPE_ITEM_VALUES[] = {
    { "\\", "\\\\" },
    { "\n", "\\n" },
    { "\t", "\\t" },
    { "\"", "\\\"" } };

OmStringEscapeItems OM_STRING_C_ESCAPE_ITEMS = {
        OM_STRING_C_ESCAPE_ITEM_VALUES,
        sizeof ( OM_STRING_C_ESCAPE_ITEM_VALUES ) / sizeof( OmStringEscapeItem ) };

const std::string OmStringEscape(
    Arg< std::string >::Type s,
    Arg< OmStringEscapeItems >::Type escapeItems )
{
    std::string res = s;
    
    ASSERT(false);
    #if 0
    OmLoopI( escapeItems.mNumItems )
    {
        res = res.ReplaceAllOccurencesOfSubstringWithString(
            OmTs( escapeItems.mpItems[ i ].mpSequenceToEscape ),
            OmTs( escapeItems.mpItems[ i ].mpEscapeSequence ) );
    }
    #endif
    
    return res;
}

#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr

std::string formatString(const char* fmt, ...) {
    size_t final_n;
    size_t n = strlen(fmt) * 2; /* Reserve two times as much as the length of the fmt_str */
    std::unique_ptr<char[]> formatted;
    va_list ap;
    while(1) {
        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
        strcpy(&formatted[0], fmt);
        va_start(ap, fmt);
        final_n = vsnprintf(&formatted[0], n, fmt, ap);
        va_end(ap);
        if (final_n < 0 || final_n >= n)
            n += abs(final_n - n + 1);
        else
            break;
    }
    return std::string(formatted.get());
}