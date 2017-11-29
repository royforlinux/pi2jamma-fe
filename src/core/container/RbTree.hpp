#pragma once

#include "core/container/RbTreeBase.hpp"
#include "core/container/LifetimePolicy.hpp"
#include "core/Compare.hpp"

template<typename T>
class RbTreeNode final : public RbTreeNodeBase
{
public:
    RbTreeNode(T item)
        : mItem(item) {
    }

    T& getItem() {
        return mItem;
    }

    const T& getItem() const {
        return mItem;
    }


    T mItem;
};

template<
    typename ItemType,
    typename KeyType,
    typename Arg<KeyType>::Type(*GetKey)(typename Arg<ItemType>::Type),
    typename LifetimePolicy = LifetimePolicyNone<ItemType> >
class RbTree final
{
public:

    ~RbTree() {
        clear();
    }

    using NodeType = RbTreeNode<ItemType>;

    void insert(NodeType& node) {
        //LogFmt("insert: %s\n", std::to_string(GetKey(node.getItem())).c_str());
        mTree.insert(
            &node,
            [](const RbTreeNodeBase* pN1, const RbTreeNodeBase* pN2) {
                return
                    Comparer<KeyType>::Compare(
                        GetKey(static_cast<const NodeType*>(pN1)->getItem()),
                        GetKey(static_cast<const NodeType*>(pN2)->getItem()));

            } );

        LifetimePolicy::addRef(node.getItem());
    }

    NodeType* find(typename Arg<KeyType>::Type key) {
        return
            const_cast<RbTreeNode<ItemType>*>(
                const_cast<const RbTree*>(this)->find(key));
    }

    const NodeType* find(typename Arg<KeyType>::Type key) const {
        const RbTreeNodeBase* pNodeBase = mTree.find(
            [&key](const RbTreeNodeBase* pRhs) {
                return
                    Comparer<KeyType>::Compare(
                        GetKey(static_cast<const NodeType*>(pRhs)->getItem()),
                        key);
            });

        return static_cast<const RbTreeNode<ItemType>*>(pNodeBase);
    } 

    const NodeType* getFirst() const {
        return static_cast<const NodeType*>(mTree.getFirst());
    }   

    NodeType* getFirst() {
        return static_cast<NodeType*>(mTree.getFirst());
    }

    const NodeType* getNext(const NodeType* pPrev) const {
        return
            static_cast<const NodeType*>(
                mTree.getNext(
                    pPrev));
    }

    NodeType* getNext(NodeType* pPrev) {
        return
            static_cast<NodeType*>(
                mTree.getNext(pPrev));
    }

    ItemType* findItem(typename Arg<KeyType>::Type key)
    {
        RbTreeNode<ItemType>* pNode = find(key);
        if(nullptr == pNode) {
            return nullptr;
        }

        return & pNode->getItem();
    }

    const ItemType* findItem(typename Arg<KeyType>::Type key) const
    {
        const RbTreeNode<ItemType>* pNode = find(key);
        if(nullptr == pNode) {
            return nullptr;
        }

        return & pNode->getItem();
    }

    void remove(NodeType& node) {
        mTree.remove(&node);
    }
    void clear() {
        for(auto&& i: *this) {
            LifetimePolicy::release(i);
        }

        mTree.clear();
    }

    class iterator {
        public:
            iterator(
                RbTree* pTree,
                RbTreeNode<ItemType>* pNode)
                : mpTree(pTree)
                , mpNode(pNode) {
            }

            bool operator !=(iterator& rhs) {
                return mpNode != rhs.mpNode;
            }

            iterator& operator++() {
                ASSERT(nullptr != mpNode);
                mpNode = mpTree->getNext(mpNode);
                return *this;
            }

            ItemType& operator*() {
                return mpNode->getItem();
            }

        private:

            RbTree* mpTree;
            RbTreeNode<ItemType>* mpNode;            
    };

    class const_iterator {
        public:
            const_iterator(
                const RbTree* pTree,
                const RbTreeNode<ItemType>* pNode)
                : mpTree(pTree)
                , mpNode(pNode) {
            }

            bool operator !=(const_iterator& rhs) {
                return mpNode != rhs.mpNode;
            }

            const_iterator& operator++() {
                ASSERT(nullptr != mpNode);
                mpNode = mpTree->getNext(mpNode);
                return *this;
            }

            const ItemType& operator*() {
                return mpNode->getItem();
            }

        private:
            
            const RbTree* mpTree;
            const RbTreeNode<ItemType>* mpNode;

    };

    iterator begin() {
        return iterator(this, getFirst());
    }

    iterator end() {
        return iterator(this, nullptr);
    }

    const_iterator begin() const {
        return const_iterator(this, getFirst());
    }

    const_iterator end() const {
        return const_iterator(this, nullptr);
    }

private:

    RbTreeBase mTree;
};

#if 0
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

#endif // HPP GUARD

