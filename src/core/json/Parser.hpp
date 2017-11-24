#pragma once

#if 0
#include "core/json/DataStream.hpp"

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
    
        size_t mColumnCount;
        size_t mLineCount;
        const std::string* mpFilename;
    
        std::vector< CharType >* mpWorkArea;
};

template< typename STREAM_TYPE>
OmParser< STREAM_TYPE>::OmParser( )
    :
    mEof( true ),
    mLineCount( 0 ),
    mColumnCount( 0 )
{
}

template< typename STREAM_TYPE>
OmParser< STREAM_TYPE>::OmParser(
    typename Arg< STREAM_TYPE >::Type stream,
    std::vector< CharType >* pWorkArea,
    const std::string* pFilename )
    :
    mStream( stream ),
    mpWorkArea( pWorkArea ),
    mpFilename( pFilename ),
    mEof( OmDecoderResult_Ok != mStream.NextChar( & mCurrentChar ) ),
    mColumnCount( 0 ),
    mLineCount( 0 )

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
    mpWorkArea->Clear();
    return mpWorkArea;
}

template< typename STREAM_TYPE>
inline const std::string OmParser< STREAM_TYPE>::StringFromWorkArea( void )
{
    return std::string( mpWorkArea->GetRawPtr(), mpWorkArea->GetCount() );
}

template< typename STREAM_TYPE>
const std::string OmParser< STREAM_TYPE>::GetErrorHint( void )
{
    std::vector< CharType > err(
        std::vector< CharType >::InitWith_Capacity, 80 );
    
    CharType c;
    
    OmLoopI( 80 )
    {
        if ( ! Peek( &c ) )
        {
            break;
        }
        
        err.PushBack( c );
        
        Next();
        
    }
    
    return OmSl( "Before:" ) + std::string( err.GetRawPtr(), err.GetCount() );
}

template< typename STREAM_TYPE>
const std::string OmParser< STREAM_TYPE>::GetFilename( void ) const
{
    if ( OmIsValid( mpFilename ) )
    {
        return *mpFilename;
    }
    
    return std::string::Empty;
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

#include "core/json/Utf8Decoder.hpp"

class OmUtf8DataParserAssembly
{
    public:
    
        typedef OmParser< OmUtf8Decoder< OmDataStream< OmUtf8Char > >  > ParserType;
    
        OmUtf8DataParserAssembly(
            const OmUtf8Char* pChar,
            size_t length,
            Arg< std::string >::Type filename = std::string::Empty )
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
            Arg< std::string >::Type filename = std::string::Empty )
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

class std::stringDecoder
{
    public:
    
        typedef OmUnicode16Char CharType;

        std::stringDecoder(
            Arg< std::string >::Type s )
            :
            mString( s ),
            mPosition( 0 ),
            mLength( s.GetLength() )
        {
        }
    
        OmDecoderResult NextChar( CharType* pChar )
        {
            if ( mPosition >= mLength )
            {
                return OmDecoderResult_Eof;
            }
            
            *pChar = mString[ mPosition ];
            
            mPosition++;
            
            return OmDecoderResult_Ok;
        }

        size_t mPosition;
        size_t mLength;
    
        std::string mString;
};

class std::stringParserAssembly
{
    public:
    
        typedef OmParser< std::stringDecoder > ParserType;
    
        std::stringParserAssembly(
            Arg< std::string >::Type s,
            Arg< std::string >::Type filename = std::string::Empty )
            :
            mFilename( filename ),
            mStringDecoder( s ),
            mParser( mStringDecoder, & mWorkArea, & filename )
        {
        }

        ParserType* GetParser( void ) { return & mParser; }
    
    private:
    
        std::string mFilename;
        ParserType::WorkAreaType mWorkArea;
        std::stringDecoder mStringDecoder;
        ParserType mParser;
};

class OmUtf8StreamParserAssembly
{
    public:
    
        typedef OmUtf8DataParserAssembly::ParserType ParserType;
    
        OmUtf8StreamParserAssembly(
            OmStream* pStream,
            Arg< std::string >::Type filename = std::string::Empty )
        {
            OmStreamRead( pStream, & mData );
            
            msptDataParser =
                OmSptFrom(
                    new OmUtf8DataParserAssembly(
                        mData.GetRawPtr(),
                        mData.GetCount(),
                        filename ) );
        }
    
        ParserType* GetParser( void ) { return msptDataParser->GetParser(); }
        
    
        std::vector< OmChar > mData;
    
        OmSpt< OmUtf8DataParserAssembly > msptDataParser;
    
};

#endif
