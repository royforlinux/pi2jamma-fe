#include "core/container/RbTreeBase.hpp"

RbTreeBase::RbTreeBase()
{
    reset();
}

RbTreeBase::~RbTreeBase()
{
    clear();
}

void RbTreeBase::reset()
{
    mSentinal.mpLeft = & mSentinal;
    mSentinal.mpRight = & mSentinal;
    mSentinal.mpParent = & mSentinal;
    mSentinal.mRed = 0;
    mRoot.mpLeft = & mSentinal;
    mRoot.mpRight = & mSentinal;
    mRoot.mpParent = & mSentinal;
    mRoot.mRed = 0; 
}

void RbTreeBase::clear()
{
    #ifdef DEBUG_CONTAINER
        auto pI = getFirst();
        while(pI)
        {
            pI->mpTree = nullptr;
            pI = getNext(pI);
        }
    #endif

}

void RbTreeBase::insert(
	RbTreeNodeBase* pItem,
	const InsertFunction& compare)
{
	#if 0
    ASSERT(
        ( ALLOW_DUPLICATES == OmAllowDuplicates_True ) ||
        OmIsNull( FindFirst( COMPARER::GetKey( pItem ) ) ) );
     #endif
    
    RbTreeNodeBase * pY = nullptr;
    RbTreeNodeBase * pX = pItem;

    #ifdef DEBUG_CONTAINER
        
        ASSERT( pX->mpTree == nullptr );
        pX->mpTree = this;
        
    #endif
    
    insertHelp(pX, compare);

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
                    leftRotate( pX );
                }
                
                pX->mpParent->mRed = 0;
                pX->mpParent->mpParent->mRed = 1;
                rightRotate( pX->mpParent->mpParent );
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
                    rightRotate( pX );
                }
                
                pX->mpParent->mRed = 0;
                pX->mpParent->mpParent->mRed = 1;
                leftRotate( pX->mpParent->mpParent );
            } 
        }
    }
    
    mRoot.mpLeft->mRed=0;
}

RbTreeNodeBase* RbTreeBase::find(const CompareFunction& compare) {
	return const_cast<RbTreeNodeBase*>(
		const_cast<RbTreeBase*>(this)->find(compare));
}

const RbTreeNodeBase* RbTreeBase::find(const CompareFunction& compare) const
{
    const RbTreeNodeBase* pX = mRoot.mpLeft;
    const RbTreeNodeBase* pSentinal= & mSentinal;
  
    int compVal;
    
    if ( pX == pSentinal )
    {
        return( 0 );
    }
    
    compVal = compare(pX);

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
        
        compVal = compare(pX);
    }

    while( true )
    {
        const RbTreeNodeBase* pPrev = predecessor( pX );
    
        if ( pPrev == pSentinal )
        {
            break;
        }
        
        compVal = compare(pPrev);

        if ( compVal != 0 )
        {
            break;
        }
        
        pX = pPrev;
    }
    
    return pX;
}

void RbTreeBase::insertHelp(
	RbTreeNodeBase* pZ,
	const InsertFunction& compare)
{
 
	RbTreeNodeBase* pX = nullptr;
	RbTreeNodeBase* pY = nullptr;
	RbTreeNodeBase* pSentinal= & mSentinal;

	pZ->mpLeft = pZ->mpRight = pSentinal;
	pY = & mRoot;
	pX = mRoot.mpLeft;

    while( pX != pSentinal)
    {
        pY = pX;
        
        if ( /* 1 == */ 1 <= compare(pX,pZ))
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
        ( pY == & mRoot) ||
        ( /* 1 == */ 1 <= compare(pY,pZ)))
    {
        pY->mpLeft = pZ;
    }
    else
    {
        pY->mpRight = pZ;
    }
}

void RbTreeBase::remove(RbTreeNodeBase* pZ)
{

    RbTreeNodeBase* pSentinal = & mSentinal;
    RbTreeNodeBase* root = & mRoot;
    
    #ifdef DEBUG_CONTAINER
        
        ASSERT( pZ->mpTree == this );
        pZ->mpTree = NULL;
        
    #endif
        
    RbTreeNodeBase* pY = ( (pZ->mpLeft == pSentinal ) || ( pZ->mpRight == pSentinal ) ) ? pZ : successor( pZ );
    
    RbTreeNodeBase* pX = ( pY->mpLeft == pSentinal ) ? pY->mpRight : pY->mpLeft;
    
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
            removeFixUp( pX );
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
            removeFixUp( pX );
        }
    }
}

void RbTreeBase::removeFixUp(RbTreeNodeBase* pX)
{
    RbTreeNodeBase* root = mRoot.mpLeft;
    RbTreeNodeBase* w;

    while( ( ! pX->mRed ) && ( root != pX ) )
    {
        if ( pX == pX->mpParent->mpLeft )
        {
            w = pX->mpParent->mpRight;
      
            if ( w->mRed )
            {
                w->mRed = 0;
                pX->mpParent->mRed = 1;
                
                leftRotate( pX->mpParent );
                
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
      
                    rightRotate( w );
                    
                    w = pX->mpParent->mpRight;
                }
    
                w->mRed = pX->mpParent->mRed;
                pX->mpParent->mRed = 0;
                w->mpRight->mRed = 0;
                
                leftRotate( pX->mpParent );
                
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
                
                rightRotate( pX->mpParent );
                
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
                    
                    leftRotate( w );
                    
                    w = pX->mpParent->mpLeft;
                }
    
                w->mRed = pX->mpParent->mRed;
                pX->mpParent->mRed = 0;
                w->mpLeft->mRed = 0;
    
                rightRotate(pX->mpParent);
    
                pX=root;
            }
        }
    }
    
    pX->mRed=0;
}



void RbTreeBase::leftRotate(RbTreeNodeBase* pX)
{
    RbTreeNodeBase* pY;
    RbTreeNodeBase* pSentinal = & mSentinal;

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

void RbTreeBase::rightRotate(RbTreeNodeBase* pY)
{
    RbTreeNodeBase* pX = nullptr;
    RbTreeNodeBase* pSentinal= & mSentinal;

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

RbTreeNodeBase* RbTreeBase::successor(RbTreeNodeBase* pX) {
    return
        const_cast<RbTreeNodeBase*>(
            const_cast<const RbTreeBase*>(this)->successor(pX));
}

const RbTreeNodeBase* RbTreeBase::successor( const RbTreeNodeBase* pX ) const
{ 
    const RbTreeNodeBase* pY = nullptr;
    const RbTreeNodeBase* pSentinal= & mSentinal;
    const RbTreeNodeBase* root=& mRoot;

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

const RbTreeNodeBase* RbTreeBase::predecessor(const RbTreeNodeBase* pX) const
{
    const RbTreeNodeBase* pY = nullptr;
    const RbTreeNodeBase* pSentinal= & mSentinal;
    const RbTreeNodeBase* root=& mRoot;

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

const RbTreeNodeBase* RbTreeBase::getFirst() const
{
    const RbTreeNodeBase* pX = mRoot.mpLeft;
    const RbTreeNodeBase* pParent = 0;
    const RbTreeNodeBase* pSentinal = & mSentinal;
    
    while( pX != pSentinal )
    {
        pParent = pX;
        pX = pX->mpLeft;
    }
    
    return pParent;
}

RbTreeNodeBase* RbTreeBase::getFirst()
{
	return
		const_cast<RbTreeNodeBase*>(
			const_cast<const RbTreeBase*>(this)->getFirst());
}

const RbTreeNodeBase* RbTreeBase::getNext(const RbTreeNodeBase* pPrev) const
{
    ASSERT(nullptr != pPrev);

    const RbTreeNodeBase* pNext = successor(pPrev);
    
    if ( pNext == ( & mSentinal ) )
    {
        return 0;
    }
    
    return pNext;
}

RbTreeNodeBase* RbTreeBase::getNext(RbTreeNodeBase* pPrev)
{
	return
		const_cast<RbTreeNodeBase*>(
			const_cast<const RbTreeBase*>(this)->getNext(pPrev));
}

const RbTreeNodeBase* RbTreeBase::findAt( size_t index ) const
{
    const RbTreeNodeBase* pS = getFirst();
    
    size_t count = 0;
    
    while(nullptr != pS)
    {
        if( count == index )
        {
            return pS;
        }
        
        pS = getNext( pS );
        
        count++;
    }
    
    ASSERT(false);
    
    return nullptr;
}

RbTreeNodeBase* RbTreeBase::findAt(size_t index)
{
    return
        const_cast<RbTreeNodeBase*>(
            const_cast<const RbTreeBase*>(this)->findAt(index));
}

const RbTreeNodeBase* RbTreeBase::getLast(void) const
{
    const RbTreeNodeBase* pX = mRoot.mpLeft;
    const RbTreeNodeBase* pParent = nullptr;
    const RbTreeNodeBase* pSentinal = & mSentinal;
    
    while( pX != pSentinal )
    {
        pParent = pX;
        pX = pX->mpRight;
    }

    return pParent;
}

RbTreeNodeBase* RbTreeBase::getLast()
{
    return
        const_cast<RbTreeNodeBase*>(
            const_cast<const RbTreeBase*>(this)->getLast());
}

const RbTreeNodeBase* RbTreeBase::getPrev(const RbTreeNodeBase* pNext) const
{
    ASSERT(nullptr != pNext);
    
    const RbTreeNodeBase* pPrev = predecessor( pNext );
    
    if ( pPrev == ( & mSentinal ) )
    {
        return nullptr;
    }
    
    return pPrev;
}

RbTreeNodeBase* RbTreeBase::getPrev(RbTreeNodeBase* pNext)
{
    return
        const_cast<RbTreeNodeBase*>(
            const_cast<const RbTreeBase*>(this)->getPrev(pNext));
}

size_t RbTreeBase::count() const
{
    const RbTreeNodeBase* pS = getFirst();
    
    size_t count = 0;
    
    while( nullptr != pS )
    {
        count++;
        pS = getNext( pS );
    }
    
    return count;
}

const RbTreeNodeBase* RbTreeBase::findClosest(
    const CompareFunction& compare) const
{
    const RbTreeNodeBase* pX = mRoot.mpLeft;
    const RbTreeNodeBase* pSentinal= & mSentinal;
  
    int compVal;
    
    if ( pX == pSentinal )
    {
        return( 0 );
    }
    
    compVal = compare(pX);
    
    while( 0 != compVal )
    {
        const RbTreeNodeBase* pPrev = pX;

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
            return pPrev;
        }
        
        compVal = compare(pX);
    }

    while( true )
    {
        const RbTreeNodeBase* pPrev = predecessor( pX );
    
        if ( pPrev == pSentinal )
        {
            break;
        }
        
        compVal = compare(pPrev);

        if ( compVal != 0 )
        {
            break;
        }
        
        pX = pPrev;
    }
    
    return pX;
}

RbTreeNodeBase* RbTreeBase::findClosest(const CompareFunction& compare)
{
    return
        const_cast<RbTreeNodeBase*>(
            const_cast<const RbTreeBase*>(this)->findClosest(compare));
}
