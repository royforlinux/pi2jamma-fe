#include "core/String.hpp"
#include <stdarg.h>

String String::Empty;

String::String(
    Type type,
    const OmChar* pCString )
{
    ASSERT( OmIsValid( pCString ) );
    
    size_t length = strlen( pCString );
    
    mType = type;
    
    if ( ( Static == type ) || ( Temp == type ) )
    {
        mStaticData.mpCString = pCString;
        mStaticData.mLength = strlen( pCString );
    }
    else
    {
        mDynamicData.mpShared = DynamicData::Shared::New( length );
        mDynamicData.mpShared->AddRef();
        strcpy( mDynamicData.mpShared->GetUtf8(), pCString );
    }
}


String::String( _InitFromMemory_, const void* pMem, size_t numBytes )
{
    mType = Dynamic;
    mDynamicData.mpShared = DynamicData::Shared::New( numBytes );
    mDynamicData.mpShared->AddRef();

    OmChar* pString = mDynamicData.mpShared->GetUtf8();

    memcpy( pString, pMem, numBytes );
    pString[ numBytes ] = 0;
}

String::String( _InitWithFormat_, const OmChar* pFormat, ... )
{
    va_list args;
    va_start( args, pFormat );
    
    char* pNewString = 0;
    
    OmUInt length = vasprintf( & pNewString, pFormat, args );

    va_end( args );
    
    mType = Dynamic;
    mDynamicData.mpShared = DynamicData::Shared::New( length );
    mDynamicData.mpShared->AddRef();
    strcpy( mDynamicData.mpShared->GetUtf8(), pNewString );
    
    free( pNewString );
}

String::String( const String& rhs )
{   
    mType = rhs.mType;

    if ( Dynamic == rhs.mType )    
    {
        mDynamicData.mpShared = rhs.mDynamicData.mpShared;
        mDynamicData.mpShared->AddRef();
    }
    else
    {
        mStaticData = rhs.mStaticData;
    }
}

String& String::operator=( const String& rhs )
{
    if ( ( & rhs ) != this )
    {
        if ( Dynamic == rhs.mType )
        {
            rhs.mDynamicData.mpShared->AddRef();
        }        
        
        if ( Dynamic == mType )
        {
            mDynamicData.mpShared->Release();
        }
        
        if ( Dynamic == rhs.mType )
        {
            mDynamicData.mpShared = rhs.mDynamicData.mpShared;
            mType = Dynamic;
        }
        else if ( Temp == rhs.mType )
        {
            mDynamicData.mpShared = DynamicData::Shared::New( rhs.mStaticData.mLength );
            mDynamicData.mpShared->AddRef();
            strcpy( mDynamicData.mpShared->GetUtf8(), rhs.mStaticData.mpCString );
            mType = Dynamic;
        }
        else // Temp
        {
            mStaticData = rhs.mStaticData;
            mType = Static;
        }
    }
    
    return *this;
}

void String::InsertObjectAtIndex( const String& s, size_t position )
{
    ASSERT( position <= GetLength() );
    
    DynamicData::Shared* pShared = DynamicData::Shared::New( s.GetLength() + GetLength() );
    
    OmChar* pNewString = pShared->GetUtf8();
    OmChar* pC = pNewString;
    
    OmUInt start = position;
    OmUInt mid = s.GetLength();
    OmUInt end = GetLength() - position;
    
    memcpy( pC, GetUtf8(), start );
    pC += start;
    memcpy( pC, s.GetUtf8(), mid );
    pC += mid;
    memcpy( pC, GetUtf8() + position, end );
    pC += end;
    
    pNewString[  pC - pNewString ] = '\0';
    
    if ( Dynamic == mType )
    {
        mDynamicData.mpShared->Release();
    }
    else
    {
        mType = Dynamic;
    }
        
    mDynamicData.mpShared = pShared;
    mDynamicData.mpShared->AddRef();
}

void String::RemoveCharsAt( size_t position, size_t numChars )
{
    ASSERT( ( position + numChars ) <= GetLength() );
    
    OmUInt oldLength = GetLength();
    OmUInt newLength = oldLength - numChars;
    
    DynamicData::Shared* pShared = DynamicData::Shared::New( newLength );

    OmChar* pNewCString = pShared->GetUtf8();
    const OmChar* pOldCString = GetUtf8();
    
    memcpy( pNewCString, GetUtf8(), position );
    memcpy( pNewCString + position, pOldCString + position + numChars, oldLength - position - numChars );
    
    pNewCString[ newLength ] = '\0';

    if ( Dynamic == mType )
    {
        mDynamicData.mpShared->Release();
    }
    else
    {
        mType = Dynamic;
    }
        
    mDynamicData.mpShared = pShared;
    mDynamicData.mpShared->AddRef();
}

String String::Right( size_t pos ) const
{
    OmUInt len = GetLength();

    if( ( 0 == pos ) || ( 0 == len ) )
    {
        return *this;
    }
    
    if ( pos >= len )
    {
        return String::Empty;
    }

    return String(
        Dynamic,
        & GetUtf8()[ pos ] );
}

String String::Left( size_t numChars ) const
{
    numChars = OmMin( numChars, GetLength() );

    return String( InitFromMemory, GetUtf8(), numChars );
}

String String::Lower( void ) const
{
    String n = String( Dynamic, GetUtf8() );
    
    OmChar* pC = n.mDynamicData.mpShared->GetUtf8();
    OmChar* pE = pC + n.GetLength();
    
    while( pC < pE )
    {
        if ( ( *pC >= 'A' ) && ( *pC <= 'Z' ) )
        {
            *pC = *pC - 'A' + 'a';
        }
        
        pC++;
    }
    
    return n;
}

OmBool OmIsValidCVariableName( const String& value )
{
    const OmUInt length = value.GetLength();
    const OmChar* pS = value.GetUtf8();

    if ( length <= 0 )
    {
        return OmFalse;
    }
    
    OmBool isValid = OmCharIsLetter( *pS );
    
    pS++;
    
    while( OmCharIsNull( OmDeRef( pS ) ) )
    {
        OmAssignAnd(
            & isValid,
            OmLogOr(
                OmCharIsLetter( OmDeRef( pS ) ),
                OmCharIsNumber( OmDeRef( pS ) ),
                OmCharIsUnderscore( OmDeRef( pS ) ) ) );
    }
    
    return isValid;
}

