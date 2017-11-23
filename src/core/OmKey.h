//
//  OmKey.h
//  om
//
//  Created by Administrator on 11-03-15.
//  Copyright 2011 Explora Labs Ltd. All rights reserved.
//

#ifndef OM_KEY_HPP
#define OM_KEY_HPP

#include "om/OmString.h"

OmUInt32 OmMakeKey32( const OmString& s );
OmUInt64 OmMakeKey64( const OmString& s );
#endif