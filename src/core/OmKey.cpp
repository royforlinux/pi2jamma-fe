//
//  OmKey.cpp
//  om
//
//  Created by Administrator on 11-03-15.
//  Copyright 2011 Explora Labs Ltd. All rights reserved.
//

#include "om/OmKey.h"

OmUInt32 OmMakeKey32( const OmString& s )
{
    OmUInt32 hash = 0;
  
    OmUInt32 length = static_cast< OmUInt32 >( s.GetLength() );
    
    OmLoopI( length )
    {
        hash = hash * 31 + ( s[ i ]);
    }
    
    return hash;
}

OmUInt64 OmMakeKey64( const OmString& s )
{
    OmUInt64 hash = 0;
  
    OmUInt64 length = s.GetLength();
    
    OmLoopI( length )
    {
        hash = hash * 63 + ( s[ i ]);
    }
    return hash;
}
