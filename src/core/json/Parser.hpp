#pragma once

#include "core/json/Decoder.hpp"
//#include "core/json/DataStream.hpp"
//#include "core/json/Utf8Decoder.hpp"

template< typename STREAM_TYPE >
class OmParser
{
    public:
    
        typedef size_t PositionType;
        typedef typename STREAM_TYPE::CharType CharType;
        typedef std::vector< CharType > WorkAreaType;
    
        OmParser( );
        OmParser(
            typename Arg< STREAM_TYPE >::Type stream,
            std::vector< CharType >* pWorkArea,
            const std::string* pFilename );

        bool Eof( void ) const;
    
        const CharType Peek( void );
        bool Peek( CharType* pChar );

        const bool Next( CharType* pCurrentChar );
        const bool Next( void );

        const bool Adv( CharType* pChar );
    
    
        std::vector< CharType >* ClearWorkArea( void );
        const std::string StringFromWorkArea( void );
    
        const std::string GetErrorHint( void );
    
        const std::string GetFilename( void ) const;
        const size_t GetLineCount( void ) const;
        const size_t GetColumnCount( void ) const;

    private:

        void AdvanceLineColumnCount( void );
    
        STREAM_TYPE mStream;
        CharType mCurrentChar;
        bool mEof;
        
        size_t mLineCount;
        size_t mColumnCount;

        const std::string* mpFilename;
    
        std::vector< CharType >* mpWorkArea;
};

template< typename STREAM_TYPE>
OmParser< STREAM_TYPE>::OmParser( )
    :
    mEof( true ),
    mLineCount( 0 ),
    mColumnCount( 0 ),
    mpFilename(nullptr),
    mpWorkArea(nullptr)
{
}

template< typename STREAM_TYPE>
OmParser< STREAM_TYPE>::OmParser(
    typename Arg< STREAM_TYPE >::Type stream,
    std::vector< CharType >* pWorkArea,
    const std::string* pFilename )
    :
    mStream( stream ),
    mCurrentChar(0),
    mEof( OmDecoderResult_Ok != mStream.NextChar( & mCurrentChar ) ),
    mLineCount( 0 ),
    mColumnCount( 0 ),
    mpFilename( pFilename ),   
    mpWorkArea( pWorkArea )    
{
}

template< typename STREAM_TYPE>
const typename OmParser< STREAM_TYPE >::CharType
OmParser< STREAM_TYPE >::Peek( void )
{
    OM_ASSERT( ! Eof() );
    
    return mCurrentChar;
}

template< typename STREAM_TYPE>
bool OmParser< STREAM_TYPE>::Peek( CharType* pChar )
{
    if ( Eof() )
    {
        return false;
    }
    
    *pChar = mCurrentChar;
    
    return true;
}

template< typename STREAM_TYPE>
const bool OmParser< STREAM_TYPE>::Next( CharType* pCurrentChar )
{
    if ( Eof() )
    {
        return false;
    }
    (*pCurrentChar) = mCurrentChar;
    
    Next();
    
    return true;
}

template< typename STREAM_TYPE>
const bool OmParser< STREAM_TYPE>::Next( void )
{
    if ( OmDecoderResult_Ok != mStream.NextChar( & mCurrentChar ) )
    {
        // TODO: Handle Error
        mCurrentChar = 0;
        mEof = true;
        return false;
    }

    AdvanceLineColumnCount();
    
    return true;
}

template< typename STREAM_TYPE>
inline const bool OmParser< STREAM_TYPE>::Adv( CharType* pChar )
{
    Next();
    
    return Peek( pChar );
}

template< typename STREAM_TYPE>
inline bool OmParser< STREAM_TYPE>::Eof( void ) const
{
    return mEof;
}

template< typename STREAM_TYPE>
inline typename OmParser< STREAM_TYPE >::WorkAreaType*
OmParser< STREAM_TYPE>::ClearWorkArea( void )
{
    mpWorkArea->clear();
    return mpWorkArea;
}

template< typename STREAM_TYPE>
inline const std::string OmParser< STREAM_TYPE>::StringFromWorkArea( void )
{
    return std::string( mpWorkArea->data(), mpWorkArea->size() );
}

template< typename STREAM_TYPE>
const std::string OmParser< STREAM_TYPE>::GetErrorHint( void )
{
    std::vector< CharType > err;
    err.reserve(80);
    
    CharType c;
    
    for(size_t i = 0; i < 80; i ++)
    {
        if ( ! Peek( &c ) )
        {
            break;
        }
        
        err.PushBack( c );
        
        Next();
        
    }
    
    return OmSl( "Before:" ) + std::string( err.data(), err.GetCount() );
}

template< typename STREAM_TYPE>
const std::string OmParser< STREAM_TYPE>::GetFilename( void ) const
{
    if ( nullptr != mpFilename )
    {
        return *mpFilename;
    }
    
    return std::string();
}

template< typename STREAM_TYPE>
const size_t OmParser< STREAM_TYPE>::GetLineCount( void ) const
{
    return mLineCount;
}

template< typename STREAM_TYPE>
const size_t OmParser< STREAM_TYPE>::GetColumnCount( void ) const
{
    return mColumnCount;
}

template< typename STREAM_TYPE>
void OmParser< STREAM_TYPE>::AdvanceLineColumnCount( void )
{
    if ( '\n' == mCurrentChar )
    {
        mLineCount++;
        mColumnCount = 0;
    }
    else
    {
        mColumnCount++;
    }
}

#if 0
#include "core/json/Utf8Decoder.hpp"

class OmUtf8DataParserAssembly
{
    public:
    
        typedef OmParser< OmUtf8Decoder< OmDataStream< OmUtf8Char > >  > ParserType;
    
        OmUtf8DataParserAssembly(
            const OmUtf8Char* pChar,
            size_t length,
            Arg< std::string >::Type filename = std::string() )
            :
            mFilename( filename ),
            mDataStream( pChar, length ),
            mUtf8Decoder( mDataStream ),
            mParser( mUtf8Decoder, & mWorkArea, & filename )
        {
        }
    
        ParserType* GetParser( void ) { return & mParser; }
    
    private:
    
        std::string mFilename;
        OmDataStream< OmUtf8Char > mDataStream;
        OmUtf8Decoder< OmDataStream< OmUtf8Char > > mUtf8Decoder;
        ParserType::WorkAreaType mWorkArea;
        ParserType mParser;
};



template< typename CHAR_TYPE >
class OmDataParserAssembly
{
    public:

        typedef OmParser< OmDataStream< CHAR_TYPE > > ParserType;
    
        OmDataParserAssembly(
            const CHAR_TYPE* pChars,
            size_t numChars,
            Arg< std::string >::Type filename = std::string() )
            :
            mFilename( filename ),
            mDataStream( pChars, numChars ),
            mParser( mDataStream, & mWorkArea, & mFilename )
        {
        }
    
    
        ParserType* GetParser( void ) { return & mParser; }
    
    private:
    
        std::string mFilename;
        OmDataStream< CHAR_TYPE > mDataStream;
        ParserType mParser;
        typename ParserType::WorkAreaType mWorkArea;
    
};

#endif

class StringDecoder
{
    public:
    
        typedef char CharType;

        StringDecoder(
            const char* pStart,
            size_t length)
            : mpString(pStart)
            , mLength(length)
            , mPosition( 0 )
        {
        }
    
        OmDecoderResult NextChar( CharType* pChar )
        {
            if ( mPosition >= mLength )
            {
                return OmDecoderResult_Eof;
            }
            
            *pChar = mpString[ mPosition ];
            
            mPosition++;
            
            return OmDecoderResult_Ok;
        }

        const char* mpString;
        size_t mLength;
        size_t mPosition;
};

class StringParserAssembly
{
    public:
    
        typedef OmParser< StringDecoder > ParserType;
    
        StringParserAssembly(
            const char* pStart,
            size_t length,
            Arg< std::string >::Type filename = std::string() )
            :
            mFilename( filename ),
            mStringDecoder(pStart, length),
            mParser( mStringDecoder, & mWorkArea, & filename )
        {
        }

        ParserType* GetParser( void ) { return & mParser; }
    
    private:
    
        std::string mFilename;
        ParserType::WorkAreaType mWorkArea;
        StringDecoder mStringDecoder;
        ParserType mParser;
};

#if 0
class OmUtf8StreamParserAssembly
{
    public:
    
        typedef OmUtf8DataParserAssembly::ParserType ParserType;
    
        OmUtf8StreamParserAssembly(
            OmStream* pStream,
            Arg< std::string >::Type filename = std::string() )
        {
            OmStreamRead( pStream, & mData );
            
            msptDataParser =
                OmSptFrom(
                    new OmUtf8DataParserAssembly(
                        mData.data(),
                        mData.GetCount(),
                        filename ) );
        }
    
        ParserType* GetParser( void ) { return msptDataParser->GetParser(); }
        
    
        std::vector< OmChar > mData;
    
        OmSpt< OmUtf8DataParserAssembly > msptDataParser;
    
};

#endif
