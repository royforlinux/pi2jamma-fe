#pragma once

#include "core/CString.hpp"
#include "core/Char.hpp"

#include <stdlib.h>

const char STRING_ID[] = "StringData";

#define Sl( CSTRING ) String( String::Static, CSTRING )
#define Ds( CSTRING ) String( String::Dynamic, CSTRING )
#define Ts( CSTRING ) String( String::Temp, CSTRING )
#define Fs( FORMATCSTRING, ARGS... ) String( String::InitWithFormat, FORMATCSTRING, ARGS )

class String
{
    public:

        static String Empty;

        enum Type {
            Static,
            Dynamic,
            Temp };
            
        enum _InitFromMemory_{
            InitFromMemory };
        
        enum _InitWithFormat_ {
            InitWithFormat };

        explicit String( Type = Static, const char* = OM_EMPTY_C_STRING );
        explicit String( _InitFromMemory_, const void*, size_t numBytes ); 
        explicit String( _InitWithFormat_, const char*, ... );
        
        String( const String& rhs );
        inline ~String( void );
        
        inline size_t GetLength( void ) const;
        
        inline char GetCharAt( size_t i ) const;
        void InsertObjectAtIndex( const String& s, size_t position );
        void RemoveCharsAt( size_t position, size_t numChars );
        
        String& operator=( const String& rhs );
        inline bool operator==( const char* pCString ) const;
        inline bool operator==( const String& rhs ) const;
        inline bool operator!=( const String& rhs ) const;
        
        inline char operator[]( size_t index ) const;
        
        inline const char* GetUtf8() const;
        inline const char* c_str() const { return GetUtf8(); }
        
        inline bool operator >( const String& rhs ) const;
        inline bool operator <( const String& rhs ) const;
        
        String Right( size_t pos ) const;
        String Left( size_t numChars ) const;
        
        String Lower( void ) const;

        String operator+(const String& rhs) const;
        String& operator +=(const String& rhs) const;
        
    private:
    
        class DynamicData
        {
            public:

                class Shared
                {
                    public:
                    
                        inline static Shared* New( size_t length );

                        inline void AddRef( void );
                        inline void Release( void );
                        inline size_t GetRefCount( void );
                        inline char* GetUtf8( void );
                        inline size_t GetLength( void );
                        
                    private:
                    
                        inline void* operator new( size_t size, void* pMem );
                        
                        inline Shared( size_t length );
                                
                        size_t mLength;
                        size_t mRefCount;
                };
                
                Shared* mpShared;
        };
        
        Type mType;

        class StaticData
        {
            public:
            
                const char* mpCString;
                size_t mLength;
        };
        
        union
        {
            DynamicData mDynamicData;
            StaticData mStaticData;
        };
        
};

using StringArg = Arg<String>::Type;

inline size_t String::GetLength( void ) const
{
    if ( Dynamic == mType )
    {
        return mDynamicData.mpShared->GetLength();
    }
    else //if ( ( Static == mType ) || ( Temp == mType ) )
    {
        return mStaticData.mLength;
    }
}

inline String::~String( void )
{
    if ( Dynamic == mType )
    {
        mDynamicData.mpShared->Release();
    }
}

inline bool String::operator==( const char* pCString ) const
{
    return 0 == strcmp( pCString, GetUtf8() );
}

inline bool String::operator==( const String& rhs ) const
{
    if ( GetLength() != rhs.GetLength() )
    {
        return false;
    }
    
    return 0 == strcmp( GetUtf8(), rhs.GetUtf8() );
}

inline bool String::operator!=( const String& rhs ) const
{
    return ! operator==( rhs );
}

inline const char* String::GetUtf8( void ) const
{
    if ( Dynamic  == mType )
    {
        return mDynamicData.mpShared->GetUtf8();
    }
    else //( ( Temp == mType ) || ( Static == mType )
    {
        return mStaticData.mpCString;
    }
}

inline char String::GetCharAt( size_t i ) const
{
    ASSERT( i < GetLength() );
    return GetUtf8()[ i ];
}

inline char String::operator[]( size_t index ) const
{
    return GetCharAt( index );
}


inline bool String::operator >( const String& rhs ) const
{
    return strcmp( GetUtf8(), rhs.GetUtf8() ) > 0;
}

inline bool String::operator <( const String& rhs ) const
{
    return strcmp( GetUtf8(), rhs.GetUtf8() ) < 0;
}


inline String UIntToString( unsigned int i )
{
    char buf[ 256 ];
    sprintf( buf, "%d", i );
    
    return String( String::Dynamic, buf );
}

inline String::DynamicData::Shared* String::DynamicData::Shared::New( size_t length )
{
    Shared* pShared = reinterpret_cast< Shared* >(
        new char*[ sizeof( Shared ) + length + 1 ] );
    new( pShared ) Shared( length );
    
    return pShared;
}

String::DynamicData::Shared::Shared( size_t length )
    : mLength( length )
    , mRefCount( 0 )
{
}
          
void String::DynamicData::Shared::AddRef( void )
{
    mRefCount++;
}

void String::DynamicData::Shared::Release( void )
{
    if ( mRefCount <= 1 )
    {
        char* pMem = reinterpret_cast< char* >( this );
        
        this->~Shared();

        delete [] pMem;
    }
    else
    {
        mRefCount--;
    }
}
size_t String::DynamicData::Shared::GetRefCount( void )
{
    return mRefCount;
}

char* String::DynamicData::Shared::GetUtf8( void )
{
    return
        reinterpret_cast< char* >( this ) +
        sizeof( *this );
}

size_t String::DynamicData::Shared::GetLength( void )
{
    return mLength;
}

inline void* String::DynamicData::Shared::operator new( size_t size, void* pMem )
{
    return pMem;
}

inline bool OmIsNumeric( const String& s )
{
    size_t numChars = s.GetLength();

    for(size_t i = 0; i < numChars; i ++ )
    {
        char c = s[ i ];
        
        if ( ! OmCharIsNumber( c ) )
        {
            return false;
        }
    }
    
    return OmTrue;
}

bool OmIsValidCVariableName( const String& s );

bool OmIsNumeric( const String& s );

unsigned int OmToUInt( const String& s );
uint32_t OmToUInt32( const String& s );
OmFloat32 OmToFloat32( const String& s );

//OM_DEFAULT_COMPARE( String );

inline unsigned int OmToUInt( const String& s )
{
    return static_cast< size_t >( atoi( s.GetUtf8() ) );
}

inline OmInt OmToInt( const String& s )
{
    return atoi( s.GetUtf8() );
}

inline uint32_t OmToUInt32( const String& s )
{
    return static_cast< uint32_t >( atoi( s.GetUtf8() ) );
}

inline OmFloat32 OmToFloat32( const String& s )
{
    return static_cast< OmFloat32 >( atof( s.GetUtf8() ) );
}



