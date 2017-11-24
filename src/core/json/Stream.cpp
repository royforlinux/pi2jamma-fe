#if 0

#include "om/OmStream.h"

OmBool OmStream::Skip( OmUInt numBytes )
{
    char buf[ OM_STREAM_STACK_BUFFER_SIZE ];
    
    OmUInt fullBlocks = numBytes / sizeof( buf );
    OmUInt lastBlockBytes = numBytes / sizeof( buf );
    
    OmLoopI( fullBlocks )
    {
        if ( ! ReadExactly( buf, sizeof( buf ) ) )
        {
            return OmFalse;
        }
    }
    
    if ( ! ReadExactly( buf, lastBlockBytes ) )
    {
        return OmFalse;
    }
    
    return OmTrue;
}

OmBool OmStream::GetIsEof( void )
{
    OM_ASSERT( GetHasLength() && GetCanSeek() );
    
    OmUInt position = 0;
    OmUInt length = 0;
    
    if ( GetLength( & length ) && GetPosition( & position ) )
    {
        return position >= length;
    }
    
    return OmTrue;
}

#endif
