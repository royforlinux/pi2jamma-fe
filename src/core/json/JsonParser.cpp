#if 0
#include "om/OmJsonParser.h"
#include "om/OmFileSystem.h"
#include "om/OmParser.h"


const OmJson OmJsonLoadFromFile( Arg< OmString >::Type filename )
{
    OmRef< OmFile > sptFile = OmFileSystem::Get()->CreateFile( );
    
    if ( ! sptFile->Open( filename, OmFile::Access_Read ) )
    {
        return OmJson();
    }
    
    OmUtf8StreamParserAssembly utf8StreamParser( sptFile.GetPtr() );
    
    OmJsonParser< OmUtf8StreamParserAssembly::ParserType > jsonParser(
        utf8StreamParser.GetParser() );
    
    OmJson json;
    
    if ( ! jsonParser.Parse( & json ) )
    {
        OM_LOG(
            "JSON ERROR: %s Line: %d\n",
            jsonParser.GetError().GetUtf8(),
            (int) utf8StreamParser.GetParser()->GetLineCount() );
    }
    
    //OM_LOG( "JSON: %s", json.Dump( 0 ).GetUtf8() );
    
    
    return json;
};

#endif