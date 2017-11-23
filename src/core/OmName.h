//-----------------------------------------------------------------------------
//
// Copyright 2010-2011 (c) Timothy E. Hinds <timothyehinds@gmail.com>
//
// All rights reserved.
//
// This file is part of the om C++ toolkit.
//
// The om C++ toolkit is NOT free software, you can NOT redistribute, view it
// modify it, or distribute it under any conditions except by express
// permission from the author.
//
//-----------------------------------------------------------------------------

#ifndef OMNAME_H
#define OMNAME_H

#include "om/OmKey.h"
#include "om/OmSerialize.h"
#include "om/OmStringizer.h"

#define OM_CONST_NAME( NAME ) \
    static const OmName NAME( OmSl( #NAME ) )
    
#define SN( X ) OmName( OmSl( X ) )

#ifdef OM_DEBUG
    #define OM_NAME_STRINGS
#endif
    
//-----------------------------------------------------------------------------
// class OmName
//-----------------------------------------------------------------------------

class OmName
{
    public:
    
        typedef OmUInt32 KeyType;
    
        inline OmName( void );
        inline OmName( const OmName& rhs );
        inline explicit OmName( const OmString& );
        inline explicit OmName( KeyType key );
        
        inline OmName& operator=( const OmName& rhs );
        
        inline OmBool IsEmpty( void ) const;

        inline OmBool operator==( const OmName& rhs ) const;
        inline OmBool operator!=( const OmName& rhs ) const;
        inline OmBool operator<( const OmName& rhs ) const;
        inline OmBool operator>( const OmName& rhs ) const;
        
        inline KeyType GetKey( void ) const;
        inline operator KeyType( void ) const;
        
        #ifdef OM_NAME_STRINGS
            inline Arg< OmString >::Type GetDebugString( void ) const;
            inline void SetDebugString( Arg< OmString >::Type s );
        #endif
        
        static const OmName Empty;
    
    private:
    
        #ifdef OM_NAME_STRINGS
            OmString mString;
        #endif
        
        KeyType mKey;
};

template<>
class OmSerializer< OmName >
{
    public:

        static inline OmBool Write( OmSerializeWriteBinaryContext* pC, Arg< OmName >::Type name );
        static inline OmBool Read( OmSerializeReadBinaryContext* pC, OmName* pName );
};

OM_DEFAULT_COMPARE( OmName );

//-----------------------------------------------------------------------------
// inline
//-----------------------------------------------------------------------------

inline OmName::OmName( void )
    :
    #ifdef OM_NAME_STRINGS
        mString( OmString::Empty ),
    #endif
    mKey( 0 )
{
}

inline OmName::OmName( const OmName& rhs )
    :
    #ifdef OM_NAME_STRINGS
        mString( rhs.mString ),
    #endif
        mKey( rhs.mKey )
{
}

inline OmName::OmName( const OmString& s )
    :
    #ifdef OM_NAME_STRINGS
        mString( s ),
    #endif
    mKey( OmMakeKey32( s ) )
{
}

inline OmName::OmName( KeyType key )
    :
    #ifdef OM_NAME_STRINGS
        mString( OmSl( "<?>" ) ),
    #endif
    mKey( key )
{

}

inline OmName& OmName::operator=( const OmName& rhs )
{
    #ifdef OM_NAME_STRINGS
        mString = rhs.mString;
    #endif
    
    mKey = rhs.mKey;
    
    return *this;
}

inline OmBool OmName::IsEmpty( void ) const
{
    return ( Empty == *this );
}

inline OmBool OmName::operator==( const OmName& rhs ) const
{
    return rhs.mKey == mKey;
}

inline OmBool OmName::operator!=( const OmName& rhs ) const
{
    return rhs.mKey != mKey;
}

inline OmBool OmName::operator<( const OmName& rhs ) const
{
    return mKey < rhs.mKey;
}

inline OmBool OmName::operator>( const OmName& rhs ) const
{
    return mKey > rhs.mKey;
}

inline OmName::KeyType OmName::GetKey( void ) const
{
    return mKey;
}

inline OmName::operator KeyType( void ) const
{
    return mKey;
}

#ifdef OM_NAME_STRINGS

    inline Arg< OmString >::Type OmName::GetDebugString( void ) const
    {
        return mString;
    }
    
    inline void OmName::SetDebugString( Arg< OmString >::Type s )
    {
        mString = s;
    }
    
#endif

inline OmBool OmSerializer< OmName >::Write( OmSerializeWriteBinaryContext* pC, Arg< OmName >::Type name )
{
    OmBool ok = OmTrue;
    
    #ifdef OM_NAME_STRINGS
    
        ok = ok &&
            OmSerializer< OmBool >::Write( pC, true );
    
        ok = ok && OmSerializer< OmString >::Write( pC, name.GetDebugString() );
        
    #else
        
        ok = ok && OmSerializer< OmBool >::Write( pC, false );
    
    #endif
    
    ok = ok && OmSerializer< OmName::KeyType >::Write( pC, name.GetKey() );
    
    return ok;
}

inline OmBool OmSerializer< OmName >::Read( OmSerializeReadBinaryContext* pC, OmName* pName )
{
    OmBool hasString = OmFalse;
    
    if ( ! OmSerializer< OmBool >::Read( pC, & hasString ) )
    {
        return OmFalse;
    }

    OmString s;
    
    if ( hasString )
    {
        if ( ! OmSerializer< OmString >::Read( pC, & s ) )
        {
            return OmFalse;
        }
    }

    OmName::KeyType key = 0;
    if ( ! OmSerializer< OmName::KeyType >::Read( pC, & key ) )
    {
        return OmFalse;
    }
    
    *pName = OmName( key );
    
    #ifdef OM_NAME_STRINGS
        pName->SetDebugString( s );
    #endif
    
    return OmTrue;
}

template<>
class OmStringizer< OmName >
{
    public:
    
        static const OmString ToString( Arg< OmName >::Type name, OmUInt indent )
        {
            #ifdef OM_NAME_STRINGS
                return name.GetDebugString();
            #else
                return OmStringizer< OmName::KeyType >::ToString( name.GetKey(), 0 );
            #endif
        }
};
        

#endif // OMNAME_H

