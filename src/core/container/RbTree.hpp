#pragma once

#include "core/container/RbTreeBase.hpp"
#include "core/container/KeyFinder.hpp"
#include "core/container/LifetimePolicy.hpp"
#include "core/container/NodeFinder.hpp"
#include "core/Compare.hpp"

template<
    typename ItemType,
    typename KeyType,
    typename KeyFinderType,
    typename NodeFinderType,
    typename LifetimePolicy = LifetimePolicyNone<ItemType> >
class RbTree final
{
public:

    ~RbTree() {
        clear();
    }

    void insert(ItemType& item) {
        mTree.insert(
            & NodeFinderType::toNode(item),
            [](const RbTreeNode* n1, const RbTreeNode* n2) {
                return
                    Comparer<KeyType>::Compare(
                        KeyFinderType::get((NodeFinderType::fromNode(*n1))),
                        KeyFinderType::get((NodeFinderType::fromNode(*n2))));

            } );

        LifetimePolicy::addRef(item);
    }

    ItemType* find(typename Arg<KeyType>::Type key) {
        return
            const_cast<ItemType*>(
                const_cast<const RbTree*>(this)->find(key));
    }

    const ItemType* find(typename Arg<KeyType>::Type key) const {
        const RbTreeNode* pNodeBase = mTree.find(
            [&key](const RbTreeNode* rhs) {
                return
                    Comparer<KeyType>::Compare(
                        KeyFinderType::get((NodeFinderType::fromNode(*rhs))),
                        key);
            });

        if(nullptr == pNodeBase) {
            return nullptr;
        }

        return & NodeFinderType::fromNode(*pNodeBase);
    }

    void remove(ItemType& item) {
        mTree.remove(& NodeFinderType::toNode(item));
        LifetimePolicy::release(item);
    }

    void clear() {

        #ifdef DEBUG_CONTAINER
            RbTreeNode* pI = mTree.getFirst();
            while(nullptr != pI) {
                RbTreeNode* pNext = mTree.getNext(pI);
                mTree.remove(pI);
                LifetimePolicy::release(NodeFinderType::fromNode(*pI));
                pI = pNext;
            }
        #else

            for(auto&& i: *this) {
                LifetimePolicy::release(i);
            }

        #endif

        mTree.clear();
    }

    template<
        typename TreeType,
        typename IterItemType,
        typename NodeType>
    class iterator {
        public:
            iterator(
                TreeType* pTree,
                NodeType* pNode)
                : mpTree(pTree)
                , mpNode(pNode) {
            }

            bool operator !=(iterator& rhs) {
                return mpNode != rhs.mpNode;
            }

            iterator& operator++() {
                ASSERT(nullptr != mpNode);
                mpNode = mpTree->mTree.getNext(mpNode);
                return *this;
            }

            IterItemType& operator*() {
                ASSERT(nullptr != mpNode);
                return NodeFinderType::fromNode(*mpNode);
            }

        private:

            TreeType* mpTree;
            NodeType* mpNode;            
    };

    using ConstIterator =
        iterator<
            const RbTree,
            const ItemType,
            const RbTreeNode>;

    using NonConstIterator =
        iterator<
            RbTree,
            ItemType,
            RbTreeNode>;

    NonConstIterator begin() {
        return NonConstIterator(this, mTree.getFirst());
    }

    NonConstIterator end() {
        return NonConstIterator(this, nullptr);
    }

    ConstIterator begin() const {
        return ConstIterator(this, mTree.getFirst());
    }

    ConstIterator end() const {
        return ConstIterator(this, nullptr);
    }

private:

    RbTreeBase mTree;
};
