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
