#pragma once

#include "core/container/LifetimePolicy.hpp"

#include <vector>
#include <algorithm>

template<typename T>
class RbTreeNode
{
public:
    RbTreeNode(const T& item)
        : mItem(item) {
    }

    T mItem;
};

template<
    typename T, 
    typename KEY_TYPE,
    typename Arg<KEY_TYPE>::Type(*GET_KEY)(typename Arg<T>::Type item),
    typename LIFETIME_POLICY = LifetimePolicyNone<T>>
class RbTree final
{
public:

    using VectorType = std::vector<RbTreeNode<T>*>;

    void insert(RbTreeNode<T>& node)
    {
        LIFETIME_POLICY::addRef(node.mItem);
        mItems.push_back(&node);
    }

    void remove(RbTreeNode<T>& node)
    {
        LIFETIME_POLICY::release(node.mItem);

        mItems.erase(
            std::find(
                mItems.begin(),
                mItems.end(),
                & node));
    }

    T* find( const KEY_TYPE& key) {


        for( auto&& n : mItems ) {

            if(key == GET_KEY(n->mItem)) {
                return & n->mItem;
            }
        }
        return nullptr;
    }

    ~RbTree() {
        for(auto& i : mItems) {
            LIFETIME_POLICY::release(i->mItem);
        }
    }

    typename VectorType::iterator begin() {
        return mItems.begin();
    }

    typename VectorType::iterator end() {
        return mItems.end();
    }
private:

    VectorType mItems;
};


#if 0

#include "om/OmCompare.h"
#include "om/OmContainer.h"
#include "om/OmUtil.h"

enum OmAllowDuplicates {
    OmAllowDuplicates_False,
    OmAllowDuplicates_True };
    
#define OM_RBTREENODE( CLASS, MEMBER ) \
    OmRbTreeNode m##MEMBER; \
        inline OmUInt GetOffsetOf##MEMBER( void ) \
        { \
            return static_cast< OmUInt > ( \
                reinterpret_cast<char*>( & m##MEMBER ) - \
                reinterpret_cast<char*>( this ) ); }

#define OM_RBTREE( CLASS, MEMBER, KEYTYPE, COMPARER, ALLOW_DUPLICATES, LIFETIME_POLICY ) \
    OmRbTree< \
        CLASS, \
        KEYTYPE, \
        OmRbTreeNodeFinder< CLASS, & CLASS::GetOffsetOf##MEMBER >, \
        COMPARER, \
        ALLOW_DUPLICATES, \
        LIFETIME_POLICY< CLASS > >

//-----------------------------------------------------------------------------
// OmRbTreeNode
//-----------------------------------------------------------------------------

class OmRbTreeNode
{
    public:
    
        OmInt mRed;
        OmRbTreeNode* mpLeft;
        OmRbTreeNode* mpRight;
        OmRbTreeNode* mpParent;
        
        #ifdef OM_DEBUG_CONTAINER
            OmRbTreeNode( void ) : mpTree( NULL ) { }
            ~OmRbTreeNode( void ) { OM_ASSERT( NULL == mpTree ); }
            void* mpTree;
        #endif
};

//-----------------------------------------------------------------------------
// OmRbTreeNodeFinder
//-----------------------------------------------------------------------------

template< typename CLASS, OmUInt (CLASS::*MEMBER)( void ) >
class OmRbTreeNodeFinder
{
    public:
 
        typedef OmRbTreeNode NodeType;
        
        static NodeType* ToNode( CLASS* );
        static CLASS* FromNode( NodeType* );
};

//-----------------------------------------------------------------------------
// OmRbTree
//-----------------------------------------------------------------------------

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
class OmRbTree
{
    public:
    
        OmRbTree( void );
        ~OmRbTree( void );
        
        void Insert( CLASS* pItem );
        void Remove( CLASS* pZ);
        
        CLASS* FindFirst( typename Arg< KEYTYPE >::Type key );
        const CLASS* FindFirst( typename Arg< KEYTYPE >::Type key ) const;

        CLASS* FindClosest( typename Arg< KEYTYPE >::Type key );
        
        CLASS* FindNext( CLASS* pPrev );
        const CLASS* FindNext( CLASS* pPrev ) const;

        CLASS* GetFirst( void );
        const CLASS* GetFirst( void ) const;

        CLASS* GetNext( CLASS* );
        const CLASS* GetNext( const CLASS* ) const;

        CLASS* GetLast( void );
        CLASS* GetPrev( CLASS* );

        OmUInt Count( void ) const;
        CLASS* FindAt( OmUInt index );

        void RemoveAll( void );
    
    private:
    
        OmRbTree( const OmRbTree& );
        OmRbTree& operator=( const OmRbTree& );
        
        void Reset( void );
        
        void LeftRotate( OmRbTreeNode* pX);
        void RightRotate( OmRbTreeNode* pY );
        void InsertHelp( OmRbTreeNode* pZ );
        OmRbTreeNode* Successor( OmRbTreeNode* pX );
        OmRbTreeNode* Predecessor( OmRbTreeNode* pX);
        void RemoveFixUp( OmRbTreeNode* pX);

        OmRbTreeNode mRoot;
        OmRbTreeNode mSentinal;
};

//-----------------------------------------------------------------------------
// Inlines
//-----------------------------------------------------------------------------

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY >::OmRbTree( void )
{
    Reset();
}


template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY >::~OmRbTree( void )
{
    RemoveAll();
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
void OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY >::Reset( void )
{
    mSentinal.mpLeft = & mSentinal;
    mSentinal.mpRight = & mSentinal;
    mSentinal.mpParent = & mSentinal;
    mSentinal.mRed = 0;
    mRoot = mSentinal; 
}
    
template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
void OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY >::RemoveAll( void )
{
    // REVIEW: don't need to balance here, but watch
    // out for destruction policies when rewriting.
     
    CLASS* pT = GetFirst();
    
    while( OmIsValid( pT ) )
    {
        CLASS* pNext = GetNext( pT );
        
        Remove( pT );
        
        pT = pNext;
        
    }

    Reset();
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::GetFirst( void )
{
    OmRbTreeNode* pX = mRoot.mpLeft;
    OmRbTreeNode* pParent = 0;
    OmRbTreeNode* pSentinal = & mSentinal;
    
    while( pX != pSentinal )
    {
        pParent = pX;
        pX = pX->mpLeft;
    }
    
    return OmCond( OmIsValid( pParent ), NODEFINDER::FromNode( pParent ), 0 );
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
const CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::GetFirst( void ) const
{
    return const_cast< OmRbTree* >( this )->GetFirst();
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::FindAt( OmUInt index )
{
    CLASS* pS = GetFirst();
    
    OmUInt count = 0;
    
    while( OmIsValid( pS ) )
    {
        if( count == index )
        {
            return pS;
        }
        
        pS = GetNext( pS );
        
        count++;
    }
    
    OM_ASSERT( OmFalse );
    
    return 0;
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::GetLast( void )
{
    OmRbTreeNode* pX = mRoot.mpLeft;
    OmRbTreeNode* pParent = 0;
    OmRbTreeNode* pSentinal = & mSentinal;
    
    while( pX != pSentinal )
    {
        pParent = pX;
        pX = pX->mpRight;
    }
    
    return OmCond( OmIsValid( pParent ), NODEFINDER::FromNode( pParent ), 0 );
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::GetPrev( CLASS* pNext )
{
    OM_ASSERT( OmIsValid( pNext ) );
    
    OmRbTreeNode* pPrev = Predecessor( NODEFINDER::ToNode( pNext ) );
    
    if ( pPrev == ( & mSentinal ) )
    {
        return 0;
    }
    
    return NODEFINDER::FromNode( pPrev );
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::GetNext( CLASS* pPrev )
{
    OM_ASSERT( OmIsValid( pPrev ) );
    OmRbTreeNode* pNext = Successor( NODEFINDER::ToNode( pPrev ) );
    
    if ( pNext == ( & mSentinal ) )
    {
        return 0;
    }
    
    return NODEFINDER::FromNode( pNext );
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
const CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::GetNext( const CLASS* pPrev ) const
{
    return
        const_cast< OmRbTree* >( this )->
            GetNext( const_cast< CLASS* >( pPrev ) );
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
OmUInt OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::Count( void ) const
{
    const CLASS* pS = GetFirst();
    
    OmUInt count = 0;
    
    while( OmIsValid( pS ) )
    {
        count++;
        pS = GetNext( pS );
    }
    
    return count;
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
void OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::Insert( CLASS* pItem )
{
    OM_ASSERT(
        ( ALLOW_DUPLICATES == OmAllowDuplicates_True ) ||
        OmIsNull( FindFirst( COMPARER::GetKey( pItem ) ) ) );
        

    
    OmRbTreeNode * pY;
    OmRbTreeNode * pX = NODEFINDER::ToNode( pItem );

    #ifdef OM_DEBUG_CONTAINER
        
        OM_ASSERT( pX->mpTree == NULL );
        pX->mpTree = this;
        
    #endif
    
    InsertHelp( pX );
    pX->mRed = 1;
  
    while( pX->mpParent->mRed )
    {
        if ( pX->mpParent == pX->mpParent->mpParent->mpLeft )
        {
            pY = pX->mpParent->mpParent->mpRight;
            
            if ( pY->mRed )
            {
                pX->mpParent->mRed = 0;
                pY->mRed = 0;
                pX->mpParent->mpParent->mRed = 1;
                pX = pX->mpParent->mpParent;
            }
            else
            {
                if (pX == pX->mpParent->mpRight)
                {
                    pX = pX->mpParent;
                    LeftRotate( pX );
                }
                
                pX->mpParent->mRed = 0;
                pX->mpParent->mpParent->mRed = 1;
                RightRotate( pX->mpParent->mpParent );
            } 
        }
        else
        {
            pY = pX->mpParent->mpParent->mpLeft;
            
            if ( pY->mRed )
            {
                pX->mpParent->mRed = 0;
                pY->mRed = 0;
                pX->mpParent->mpParent->mRed = 1;
                pX = pX->mpParent->mpParent;
            }
            else
            {
                if ( pX == pX->mpParent->mpLeft )
                {
                    pX = pX->mpParent;
                    RightRotate( pX );
                }
                
                pX->mpParent->mRed = 0;
                pX->mpParent->mpParent->mRed = 1;
                LeftRotate( pX->mpParent->mpParent );
            } 
        }
    }
    
    mRoot.mpLeft->mRed=0;
    
    LIFETIME_POLICY::Add( pItem );
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY>
void OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY >::LeftRotate( OmRbTreeNode* pX)
{
    OmRbTreeNode* pY;
    OmRbTreeNode* pSentinal = & mSentinal;

    pY = pX->mpRight;
    pX->mpRight = pY->mpLeft;

    if ( pY->mpLeft != pSentinal )
    {
        pY->mpLeft->mpParent=pX;
    }

    pY->mpParent = pX->mpParent;   

    if( pX == pX->mpParent->mpLeft)
    {
        pX->mpParent->mpLeft=pY;
    }
    else
    {
        pX->mpParent->mpRight=pY;
    }
    
    pY->mpLeft = pX;
    pX->mpParent = pY;
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
void OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::RightRotate( OmRbTreeNode* pY)
{
    OmRbTreeNode* pX;
    OmRbTreeNode* pSentinal= & mSentinal;

    pX = pY->mpLeft;
    pY->mpLeft = pX->mpRight;

    if ( pSentinal != pX->mpRight )
    {
        pX->mpRight->mpParent=pY;
    }
    
    pX->mpParent = pY->mpParent;
    
    if( pY == pY->mpParent->mpLeft )
    {
        pY->mpParent->mpLeft = pX;
    }
    else
    {
        pY->mpParent->mpRight = pX;
    }
    
    pX->mpRight = pY;
    pY->mpParent = pX;
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
void OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::InsertHelp( OmRbTreeNode* pZ )
{
  OmRbTreeNode* pX;
  OmRbTreeNode* pY;
  OmRbTreeNode* pSentinal= & mSentinal;
  
  pZ->mpLeft = pZ->mpRight = pSentinal;
  pY = & mRoot;
  pX = mRoot.mpLeft;
  
    while( pX != pSentinal)
    {
        pY = pX;
        
        if ( /* 1 == */ 1 <= OmCompare(
            COMPARER::GetKey( NODEFINDER::FromNode( pX ) ),
            COMPARER::GetKey( NODEFINDER::FromNode( pZ ) ) ) )
        {
            pX=pX->mpLeft;
        }
        else
        {
            pX=pX->mpRight;
        }
    }

    pZ->mpParent = pY;
    
    if (
        ( pY == & mRoot ) ||
        ( /* 1 == */ 1 <= OmCompare(
            COMPARER::GetKey( NODEFINDER::FromNode( pY ) ),
            COMPARER::GetKey( NODEFINDER::FromNode( pZ ) ) ) ) )
    {
        pY->mpLeft = pZ;
    }
    else
    {
        pY->mpRight = pZ;
    }
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
OmRbTreeNode* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::Successor( OmRbTreeNode* pX )
{ 
    OmRbTreeNode* pY;
    OmRbTreeNode* pSentinal= & mSentinal;
    OmRbTreeNode* root=& mRoot;

    if ( pSentinal != ( pY = pX->mpRight) )
    {
        while( pY->mpLeft != pSentinal )
        { 
            pY = pY->mpLeft;
        }
        return( pY );
    }
    else
    {
        pY = pX->mpParent;
        
        while( pX == pY->mpRight )
        {
            pX = pY;
            pY = pY->mpParent;
        }
        
        if ( pY == root )
        {
            return( pSentinal );
        }
        
        return(pY);
    }
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
OmRbTreeNode* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::Predecessor( OmRbTreeNode* pX)
{
    OmRbTreeNode* pY;
    OmRbTreeNode* pSentinal= & mSentinal;
    OmRbTreeNode* root=& mRoot;

    if ( pSentinal != ( pY = pX->mpLeft ) )
    {
        while( pY->mpRight != pSentinal )
        {
            pY = pY->mpRight;
        }
        
        return( pY );
    }
    else
    {
        pY = pX->mpParent;
    
        while( pX == pY->mpLeft )
        { 
            if ( pY == root )
            {
                return( pSentinal );
            }
            
            pX = pY;
            pY = pY->mpParent;
        }
    
        return( pY );
    }
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
const CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY >::FindFirst( typename Arg< KEYTYPE >::Type key ) const
{
    return ((OmRbTree*)this)->FindFirst( key );
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY >::FindFirst( typename Arg< KEYTYPE >::Type key )
{
    OmRbTreeNode* pX = mRoot.mpLeft;
    OmRbTreeNode* pSentinal= & mSentinal;
  
    OmInt compVal;
    
    if ( pX == pSentinal )
    {
        return( 0 );
    }
    
    compVal = OmCompare(
        COMPARER::GetKey(
            NODEFINDER::FromNode( pX ) ),
            key );
    
    while( 0 != compVal )
    {
        if ( compVal >= 1 )
        {
            pX = pX->mpLeft;
        }
        else
        {
            pX = pX->mpRight;
        }
        
        if ( pX == pSentinal )
        {
            return( 0 );
        }
        
        compVal = OmCompare(
            COMPARER::GetKey(
                NODEFINDER::FromNode( pX ) ),
                key);
    }

    while( OmTrue )
    {
        OmRbTreeNode* pPrev = Predecessor( pX );
    
        if ( pPrev == pSentinal )
        {
            break;
        }
        
        compVal = OmCompare(
            COMPARER::GetKey(
                NODEFINDER::FromNode( pPrev ) ),
                key );

        if ( compVal != 0 )
        {
            break;
        }
        
        pX = pPrev;
    }
    
    return( NODEFINDER::FromNode( pX ) );
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY >::FindClosest( typename Arg< KEYTYPE >::Type key )
{
    OmRbTreeNode* pX = mRoot.mpLeft;
    OmRbTreeNode* pSentinal= & mSentinal;
  
    OmInt compVal;
    
    if ( pX == pSentinal )
    {
        return( 0 );
    }
    
    compVal = OmCompare(
        COMPARER::GetKey(
            NODEFINDER::FromNode( pX ) ),
            key );
    
    while( 0 != compVal )
    {
        OmRbTreeNode* pPrev = pX;

        if ( compVal >= 1 )
        {
            pX = pX->mpLeft;
        }
        else
        {
            pX = pX->mpRight;
        }
        
        if ( pX == pSentinal )
        {
            return NODEFINDER::FromNode( pPrev );
        }
        
        compVal = OmCompare(
            COMPARER::GetKey(
                NODEFINDER::FromNode( pX ) ),
                key);
    }

    while( OmTrue )
    {
        OmRbTreeNode* pPrev = Predecessor( pX );
    
        if ( pPrev == pSentinal )
        {
            break;
        }
        
        compVal = OmCompare(
            COMPARER::GetKey(
                NODEFINDER::FromNode( pPrev ) ),
                key );

        if ( compVal != 0 )
        {
            break;
        }
        
        pX = pPrev;
    }
    
    return( NODEFINDER::FromNode( pX ) );
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
const CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY >::FindNext( CLASS* pPrev ) const
{
    return ((OmRbTree*)this)->FindNext( pPrev );
}

template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
CLASS* OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY >::FindNext( CLASS* pPrev )
{
    OM_ASSERT( OmIsValid( pPrev ) );
    
    OmRbTreeNode* pS = Successor( NODEFINDER::ToNode( pPrev ) );
    
    if ( pS == & mSentinal )
    {
        return NULL;
    }
    
    KEYTYPE k = COMPARER::GetKey( pPrev );
    
    CLASS* pSo = NODEFINDER::FromNode( pS );
    
    OmInt compVal = OmCompare(
        COMPARER::GetKey(
            pSo),
            k );    
            
    if( 0 != compVal )
    {
        return NULL;
    }
    
    return pSo;
}


template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
void OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::RemoveFixUp( OmRbTreeNode* pX)
{
    OmRbTreeNode* root = mRoot.mpLeft;
    OmRbTreeNode* w;

    while( ( ! pX->mRed ) && ( root != pX ) )
    {
        if ( pX == pX->mpParent->mpLeft )
        {
            w = pX->mpParent->mpRight;
      
            if ( w->mRed )
            {
                w->mRed = 0;
                pX->mpParent->mRed = 1;
                
                LeftRotate( pX->mpParent );
                
                w = pX->mpParent->mpRight;
            }
            if ( ( ! w->mpRight->mRed ) && ( ! w->mpLeft->mRed ) )
            { 
                w->mRed = 1;
                pX = pX->mpParent;
            }
            else
            {
                if ( ! w->mpRight->mRed )
                {
                    w->mpLeft->mRed = 0;
                    w->mRed = 1;
	  
                    RightRotate( w );
                    
                    w = pX->mpParent->mpRight;
                }
	
                w->mRed = pX->mpParent->mRed;
                pX->mpParent->mRed = 0;
                w->mpRight->mRed = 0;
                
                LeftRotate( pX->mpParent );
                
                pX = root;
            }
        }
        else
        {
            w = pX->mpParent->mpLeft;
      
            if ( w->mRed )
            {
                w->mRed = 0;
                
                pX->mpParent->mRed = 1;
                
                RightRotate( pX->mpParent );
                
                w = pX->mpParent->mpLeft;
            }
            
            if ( ( ! w->mpRight->mRed ) && ( ! w->mpLeft->mRed ) )
            { 
                w->mRed = 1;
                pX = pX->mpParent;
            }
            else
            {
                if ( ! w->mpLeft->mRed )
                {
                    w->mpRight->mRed = 0;
                    w->mRed = 1;
                    
                    LeftRotate( w );
                    
                    w = pX->mpParent->mpLeft;
                }
	
                w->mRed = pX->mpParent->mRed;
                pX->mpParent->mRed = 0;
                w->mpLeft->mRed = 0;
	
                RightRotate(pX->mpParent);
	
                pX=root;
            }
        }
    }
    
    pX->mRed=0;
}


template<
    typename CLASS,
    typename KEYTYPE,
    typename NODEFINDER,
    typename COMPARER,
    OmAllowDuplicates ALLOW_DUPLICATES,
    typename LIFETIME_POLICY >
void OmRbTree<
    CLASS,
    KEYTYPE,
    NODEFINDER,
    COMPARER,
    ALLOW_DUPLICATES,
    LIFETIME_POLICY  >::Remove( CLASS* pZClass )
{
    OmRbTreeNode* pY;
    OmRbTreeNode* pX;
    OmRbTreeNode* pSentinal = & mSentinal;
    OmRbTreeNode* root = & mRoot;
    OmRbTreeNode* pZ = NODEFINDER::ToNode( pZClass );
    
    #ifdef OM_DEBUG_CONTAINER
        
        OM_ASSERT( pZ->mpTree == this );
        pZ->mpTree = NULL;
        
    #endif
        
    pY = ( (pZ->mpLeft == pSentinal ) || ( pZ->mpRight == pSentinal ) ) ? pZ : Successor( pZ );
    
    pX = ( pY->mpLeft == pSentinal ) ? pY->mpRight : pY->mpLeft;
    
    if ( root == ( pX->mpParent = pY->mpParent ) )
    {
        root->mpLeft = pX;
    }
    else
    {
        if ( pY == pY->mpParent->mpLeft )
        {
            pY->mpParent->mpLeft = pX;
        }
        else
        {
            pY->mpParent->mpRight=pX;
        }
    }
  
    if ( pY != pZ )
    {
        if ( ! ( pY->mRed ) )
        {
            RemoveFixUp( pX );
        }
  
        pY->mpLeft = pZ->mpLeft;
        pY->mpRight = pZ->mpRight;
        pY->mpParent = pZ->mpParent;
        pY->mRed = pZ->mRed;
        pZ->mpLeft->mpParent = pZ->mpRight->mpParent = pY;
        
        if ( pZ == pZ->mpParent->mpLeft )
        {
            pZ->mpParent->mpLeft = pY; 
        }
        else
        {
            pZ->mpParent->mpRight=pY;
        }
    }
    else
    {
        if ( ! ( pY->mRed ) )
        {
            RemoveFixUp( pX );
        }
    }
    
    LIFETIME_POLICY::Remove( pZClass );
}


template< typename TYPE, OmUInt (TYPE::*MEMBER)( void ) >
typename OmRbTreeNodeFinder< TYPE, MEMBER >::NodeType* OmRbTreeNodeFinder< TYPE, MEMBER >::ToNode( TYPE* pItem )
{
    NodeType* pNode =
        reinterpret_cast< NodeType* >(
            reinterpret_cast< char* >( pItem ) + (pItem->*MEMBER)() );
            
    return pNode;
}

template< typename TYPE, OmUInt (TYPE::*MEMBER)( void ) >
TYPE* OmRbTreeNodeFinder< TYPE, MEMBER >::FromNode( OmRbTreeNodeFinder< TYPE, MEMBER >::NodeType* pNode )
{
    TYPE* pTest = 0;
    
    TYPE* pT =
        reinterpret_cast<TYPE*>(
            reinterpret_cast< char* >( pNode ) - (pTest->*MEMBER)() );
    return pT;
}

#endif // HPP GUARD

