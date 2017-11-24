#pragma once

#if 0
const size_t OM_STREAM_STACK_BUFFER_SIZE = 4096;

//-----------------------------------------------------------------------------
// class OmStream
//-----------------------------------------------------------------------------

class OmStream : public OmRefCounted
{
    public:

        static const size_t CAN_READ = ( 1 << 0 ); // ReadUpTo()
        static const size_t CAN_WRITE = ( 1 << 1 ); // Write()
        static const size_t HAS_LENGTH = ( 1 << 2 ); // GetLength()
        static const size_t CAN_SEEK = ( 1 << 3 ); // SetPosition() / GetPosition()
        static const size_t FULL_SUPPORT = 0xFFFFFFFF;
    
        OmStream( size_t flags /* = 0 */ );
    
        virtual ~OmStream( void ) { }
    
        // Implement these:
        
        virtual bool ReadUpTo( void* pBuf, size_t maxBytes, size_t* pBytesRead );
        virtual bool Write( const void* pBuf, size_t numBytes );
        virtual const OmRef< const OmError > GetError( void );
        virtual bool SetPosition( size_t position );
        virtual bool GetPosition( size_t* pPosition );
        virtual bool GetLength( size_t* pLength );
    
        // Optionally Implement this (will read into to temp buffer to skip by
        // default )
    
        virtual bool Skip( size_t numBytes );
        virtual bool GetIsEof( void );
    
        // Helper functions
        
        bool ReadExactly( void * pBuf, size_t numBytes );
        const OmString GetErrorMessage( void );
    
        bool GetCanRead( void ) const;
        bool GetCanWrite( void ) const;
        bool GetHasLength( void ) const;
        bool GetCanSeek( void ) const;

    protected:
    
        void SetFlags( size_t flags );
    
    private:
    
        size_t mFlags;
};

//-----------------------------------------------------------------------------
// class Helper Functions
//-----------------------------------------------------------------------------

template<
    typename CONTAINER_TYPE,
    size_t BUF_SIZE = OM_STREAM_STACK_BUFFER_SIZE >
bool OmStreamRead(
    OmStream* pStream,
    CONTAINER_TYPE* pContainer,
    size_t* pBytesRead = NULL );

template< size_t BUF_SIZE = OM_STREAM_STACK_BUFFER_SIZE >
bool OmStreamAppend(
    OmStream* pStreamToAppendTo,
    OmStream* pStreamToAppend );

//-----------------------------------------------------------------------------
// inlines
//-----------------------------------------------------------------------------

inline OmStream::OmStream( size_t flags )
    :
    mFlags( flags )
{
}

inline void OmStream::SetFlags( size_t flags )
{
    mFlags = flags;
}

inline bool OmStream::ReadUpTo( void* pBuf, size_t maxBytes, size_t* pBytesRead )
{
    *pBytesRead = 0;
    return OmFalse;
}

inline bool OmStream::Write( const void* pBuf, size_t numBytes )
{
    return OmFalse;
}

inline bool OmStream::SetPosition( size_t position )
{
    return OmFalse;
}

inline bool OmStream::GetPosition( size_t* pPosition )
{
    *pPosition = 0;
    return OmFalse;
}

inline bool OmStream::GetLength( size_t* pLength )
{
    *pLength = 0;
    return OmFalse;
}

inline const OmRef< const OmError > OmStream::GetError( void )
{
    return NULL;
}

inline bool OmStream::ReadExactly( void * pBuf, size_t numBytes )
{
    size_t bytesRead = 0;
    
    if ( ! ReadUpTo( pBuf, numBytes, & bytesRead ) )
    {
        return OmFalse;
    }
    
    return ( bytesRead == numBytes );
}

inline const OmString OmStream::GetErrorMessage( void )
{
    OmRef< const OmError > sptError = GetError();
    
    if ( sptError.IsValid() )
    {
        return sptError->GetDescription();
    }
    
    return OmString::Empty;
}

inline bool OmStream::GetCanRead( void ) const
{
    return OmBitIsSet( mFlags, CAN_READ );
}

inline bool OmStream::GetCanWrite( void ) const
{
    return OmBitIsSet( mFlags, CAN_WRITE );
}

inline bool OmStream::GetHasLength( void ) const
{
    return OmBitIsSet( mFlags, HAS_LENGTH );
}

inline bool OmStream::GetCanSeek( void ) const
{
    return OmBitIsSet( mFlags, CAN_SEEK );
}

template<
    typename CONTAINER_TYPE,
    size_t BUF_SIZE  >
bool OmStreamRead(
    OmStream* pStream,
    CONTAINER_TYPE* pContainer,
    size_t* pTotalBytesRead  )
{
    typedef typename CONTAINER_TYPE::ElementType Type;
    
    OM_STATIC_ASSERT( 1 == sizeof( Type ) );
    OM_STATIC_ASSERT( OmType< Type >::IsBasic );
    
    if ( pStream->GetHasLength() )
    {
        size_t streamLength = 0;
        
        if ( ! pStream->GetLength( & streamLength ) )
        {
            OmSetIfValid( pTotalBytesRead, 0 );

            return OmFalse;
        }
        
        typedef typename CONTAINER_TYPE::ElementType Type;
        
        OM_STATIC_ASSERT( sizeof( Type ) == 1 );
        OM_STATIC_ASSERT( OmType< Type >::IsBasic );
        
        size_t elementSize = sizeof( Type );
        
        size_t fullBlocks = streamLength / elementSize;
        size_t partialBlocks = streamLength % elementSize;
        
        OM_ASSERT( 0 == partialBlocks );
        
        pContainer->Resize( fullBlocks );
        
        if ( ! pStream->ReadExactly( pContainer->GetRawPtr(), streamLength ) )
        {
            OmSetIfValid( pTotalBytesRead, 0 );
            return OmFalse;
        }
        
        OmSetIfValid( pTotalBytesRead, streamLength );
        
        return OmTrue;
    }
    else
    {
        size_t totalBytesRead = 0;
        
        Type buf[ BUF_SIZE ];
        
        OmLoopInf
        {
            size_t bytesRead = 0;
            
            if ( ! pStream->ReadUpTo( buf, BUF_SIZE, & bytesRead ) )
            {
                if ( OmIsValid( pTotalBytesRead ) )
                {
                    *pTotalBytesRead = 0;
                }
                return OmFalse;
            }
            
            totalBytesRead += bytesRead;
            
            if ( 0 == bytesRead )
            {
                if ( OmIsValid( pTotalBytesRead ) )
                {
                    *pTotalBytesRead = totalBytesRead;
                }
                return OmTrue;
            }
            
            pContainer->PushBack( buf, bytesRead );
        }
    }
}

template< size_t BUF_SIZE >
bool OmStreamAppend( OmStream* pStreamToAppendTo, OmStream* pStreamToAppend )
{
    char buf[ BUF_SIZE ];
    
    OmLoopInf
    {
        size_t bytesRead = 0;
        
        if ( ! pStreamToAppend->ReadUpTo( buf, BUF_SIZE, & bytesRead ) )
        {
            return OmFalse;
        }
        
        if ( 0 == bytesRead )
        {
            return OmTrue;
        }
        
        if ( ! pStreamToAppendTo->Write( buf, bytesRead ) )
        {
            return OmFalse;
        }
    }
}





#endif
