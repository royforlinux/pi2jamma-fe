#if 0

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

#ifndef __OMSLLIST_HPP__
#define __OMSLLIST_HPP__

#include "om/OmContainer.h"
#include "om/OmNonCopyable.h"
#include "om/OmUtil.h"

#define OM_SLLIST( CLASS, MEMBER, LIFETIME_POLICY ) \
    OmSlList< \
        CLASS, \
        OmSlListNodeFinder< CLASS, & CLASS::GetOffsetOf##MEMBER >, \
        LIFETIME_POLICY< CLASS > >

#define OM_SLLISTNODE( CLASS, MEMBER ) \
    OmSlListNode< CLASS > m##MEMBER; \
        inline OmUInt GetOffsetOf##MEMBER( void ) \
        { return reinterpret_cast<char*>( & m##MEMBER ) - \
            reinterpret_cast<char*>( this ); }
            
//-----------------------------------------------------------------------------
// OmSlListNode
//-----------------------------------------------------------------------------
            
template< typename T >
class OmSlListNode : public OmNonCopyable
{
    public:
    
        #ifdef OM_DEBUG
    
            OmSlListNode( void ) : mpParent( 0 ) { }
            ~OmSlListNode( void ) { OM_ASSERT( OmIsNull( mpParent ) ); }

        #endif

        T* mpNext;
        
        #ifdef OM_DEBUG
        
            void* mpParent;
            
        #endif    
};

//-----------------------------------------------------------------------------
// OmSlListNodeFinder
//-----------------------------------------------------------------------------

template< typename CLASS, OmUInt (CLASS::*MEMBER)( void ) >
class OmSlListNodeFinder
{
    public:
 
        typedef OmSlListNode< CLASS > NodeType;
        
        static OmSlListNode< CLASS >* ToNode( CLASS* );
        static CLASS* FromNode( OmSlListNode< CLASS >* );
};

//-----------------------------------------------------------------------------
// OmSlList
//-----------------------------------------------------------------------------

template< typename T, typename NODE_FINDER, typename LIFETIME_POLICY >
class OmSlList
{
    public:
    
        typedef OmSlListNode< T > NodeType;
        
        OmSlList( void );
        OmSlList( const OmSlList& );
        
        ~OmSlList( void );
        
        void InsertHead( T* );
        void InsertTail( T* );
        
        void Remove( T* );
        void RemoveAll( void );
        
        T* GetFirst( void );
        const T* GetFirst( void ) const;

        T* GetNext( T* pPrev );
        const T* GetNext( const T* pPrev ) const;
        
        T* FindAt( OmUInt index );
        
        OmUInt Count( void ) const;
        OmUInt FindIndexOf( T* );
                
    private:
    
        inline void RemoveNoLifetime( T* );

        void operator= (const OmSlList& list );

        T* mpHead;
};

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
OmSlList< T, NODEFINDER, LIFETIME_POLICY >::OmSlList( void )
{
    mpHead = 0;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
OmSlList< T, NODEFINDER, LIFETIME_POLICY >::OmSlList( const OmSlList& rhs )
{
    OM_ASSERT( OmIsNull( rhs.mpHead ) );
    OM_ASSERT( OmIsNull( rhs.mpTail ) );
    
    mpHead = 0;
}


template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
OmSlList< T, NODEFINDER, LIFETIME_POLICY >::~OmSlList( void )
{
    RemoveAll();
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
OmUInt OmSlList< T, NODEFINDER, LIFETIME_POLICY >::Count( void ) const
{
    OmUInt count = 0;
    
    const T* pT = GetFirst();
    
    while( OmIsValid( pT ) )
    {
        count++;
        pT = GetPrev( pT );
    }
    
    return count;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
OmUInt OmSlList< T, NODEFINDER, LIFETIME_POLICY >::FindIndexOf( T* pItem )
{
    OmUInt count = 0;
    
    T* pT = GetFirst();
    
    while( OmIsValid( pT ) )
    {
        if ( pItem == pT )
        {
            return count;
        }
        count++;
        pT = GetNext( pT );
    }
    
    OM_ASSERT( OmFalse );
    return -1;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
T* OmSlList< T, NODEFINDER, LIFETIME_POLICY >::FindAt( OmUInt index )
{
    T* pT = GetFirst();
    
    OM_ASSERT( OmIsValid( pT ) );
    
    OmLoopI( index + 1 )
    {
        if ( i == index )
        {
            return pT;
        }
        
        pT = GetNext( pT );
        
        OM_ASSERT( OmIsValid( pT ) );
    }

    OM_ASSERT( OmFalse );
    
    return 0;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
void OmSlList< T, NODEFINDER, LIFETIME_POLICY >::InsertHead( T* pItem )
{
    LIFETIME_POLICY::Add( pItem );
    
    NodeType* pNode = NODEFINDER::ToNode( pItem );
    
    #ifdef OM_DEBUG
        OM_ASSERT( OmIsNull( pNode->mpParent ) );
        pNode->mpParent = this;
    #endif
    
    pNode->mpNext = mpHead;
    
    NODEFINDER::ToNode( mpHead )->mpPrev = pItem;

    mpHead = pItem;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
void OmSlList< T, NODEFINDER, LIFETIME_POLICY >::InsertAfter( T* pItem )
{
    LIFETIME_POLICY::Add( pItem );
    
    NodeType* pNode = NODEFINDER::ToNode( pItem );

    #ifdef OM_DEBUG

        OM_ASSERT( OmIsNull( pNode->mpParent ) );
        pNode->mpParent = this;
        
    #endif
    
    NodeType* pTemp = pNode->mpNext;
    
    pNode->mpNext = NODEFINDER::FromNode( pItem );
    
    pItem->mpNext = NODEFINDER::FromNode( pTemp );
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
void OmSlList< T, NODEFINDER, LIFETIME_POLICY >::RemoveNoLifetime( T* pItem )
{
    NodeType* pNode = NODEFINDER::ToNode( pItem );
    
    #ifdef OM_DEBUG
        
        OM_ASSERT( this == pNode->mpParent );
        pNode->mpParent = 0;
        
    #endif
 
    if ( 0 != pNode->mpNext )
    {
        NODEFINDER::ToNode( pNode->mpNext )->mpPrev = pNode->mpPrev;
    }
    else
    {
        mpTail = pNode->mpPrev;
    }
    
    if ( 0 != pNode->mpPrev )
    {
        NODEFINDER::ToNode( pNode->mpPrev )->mpNext = pNode->mpNext;
    }
    else
    {
        mpHead = pNode->mpNext;
    }
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
void OmSlList< T, NODEFINDER, LIFETIME_POLICY >::Remove( T* pItem )
{
    RemoveNoLifetime( pItem );
    
    LIFETIME_POLICY::Remove( pItem );
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
void OmSlList< T, NODEFINDER, LIFETIME_POLICY >::MoveToHead( T* pItem )
{
    RemoveNoLifetime( pItem );
    InsertHead( pItem );
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
void OmSlList< T, NODEFINDER, LIFETIME_POLICY >::MoveToTail( T* pItem )
{
    RemoveNoLifetime( pItem );
    InsertTail( pItem );
}



template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
T* OmSlList< T, NODEFINDER, LIFETIME_POLICY >::GetFirst( void )
{
    return mpHead;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
const T* OmSlList< T, NODEFINDER, LIFETIME_POLICY >::GetFirst( void ) const
{
    return mpHead;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
T* OmSlList< T, NODEFINDER, LIFETIME_POLICY >::GetNext( T* pT )
{
    OM_ASSERT( 0 != pT );
    
    #ifdef OM_DEBUG
        OM_ASSERT( this == NODEFINDER::ToNode( pT )->mpParent );
    #endif
    
    T* pNext = NODEFINDER::ToNode( pT )->mpNext;
    
    return pNext;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
const T* OmSlList< T, NODEFINDER, LIFETIME_POLICY >::
GetNext( const T* pT ) const
{
    OM_ASSERT( 0 != pT );
    
    #ifdef OM_DEBUG
        OM_ASSERT( this == NODEFINDER::ToNode( (T*) pT )->mpParent );
    #endif
    
    const T* pNext = NODEFINDER::ToNode( (T*) pT )->mpNext;
    
    return pNext;
}


template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
T* OmSlList< T, NODEFINDER, LIFETIME_POLICY >::GetLast( void )
{
    return mpTail;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
const T* OmSlList< T, NODEFINDER, LIFETIME_POLICY >::GetLast( void ) const
{
    return mpTail;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
T* OmSlList< T, NODEFINDER, LIFETIME_POLICY >::GetPrev( T* pT )
{
    OM_ASSERT( pT );
 
    #ifdef OM_DEBUG
        OM_ASSERT( this == NODEFINDER::ToNode( pT )->mpParent );
    #endif
    
    T* pPrev = NODEFINDER::ToNode( pT )->mpPrev;
    
    return pPrev;
}

template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
const T* OmSlList< T, NODEFINDER, LIFETIME_POLICY >::
GetPrev( const T* pT ) const
{
    return ((OmSlList*)this)->GetPrev( (T*) pT );
}


template< typename T, typename NODEFINDER, typename LIFETIME_POLICY >
void OmSlList< T, NODEFINDER, LIFETIME_POLICY >::RemoveAll( void )
{
    #ifdef OM_DEBUG
    
        T* pI = GetFirst();
        
        while( OmIsValid( pI ) )
        {
            Remove( pI );
            
            pI = GetFirst();
        }
        
    #endif
    
    mpHead = 0;
    mpTail = 0;
}

template< typename TYPE, OmUInt (TYPE::*MEMBER)( void ) >
OmSlListNode< TYPE >* OmSlListNodeFinder< TYPE, MEMBER >::ToNode( TYPE* pItem )
{
    OmSlListNode< TYPE >* pNode =
        reinterpret_cast< NodeType* >(
            reinterpret_cast< char* >( pItem ) + (pItem->*MEMBER)() );
            
    return pNode;
}

template< typename TYPE, OmUInt (TYPE::*MEMBER)( void ) >
TYPE* OmSlListNodeFinder< TYPE, MEMBER >::FromNode( OmSlListNode< TYPE >* pNode )
{
    TYPE* pTest = 0;
    
    TYPE* pT =
        reinterpret_cast<TYPE*>(
            reinterpret_cast< char* >( pNode ) - (pTest->*MEMBER)() );
    return pT;
}

#endif // HPP Guard

#endif
