#pragma once

#include "core/container/RbTreeBase.hpp"
#include "core/container/LifetimePolicy.hpp"
#include "core/Compare.hpp"

template<typename ItemType, RbTreeNode ItemType::*Member >
struct NodeFinderField
{
    static size_t offset() {

        RbTreeNode& member = ((ItemType*)(nullptr))->*Member;

        const size_t o =
            reinterpret_cast<char*>(&member)
                - reinterpret_cast<char*>((ItemType*)(nullptr));   

        return o;   
    }

    static ItemType& fromNode(const RbTreeNode& node) {
        return
            *reinterpret_cast<ItemType*>(
                const_cast<char*>(
                    reinterpret_cast<const char*>(&node) - offset()));
    }

    static RbTreeNode& toNode(const ItemType& itemType) {
        return *((RbTreeNode*)(& (itemType.*Member)));
    }
};

template<typename ItemType, typename KeyType, typename Arg<KeyType>::Type (ItemType::*Getter)() const>
struct KeyFinderGetter
{
    static typename Arg<KeyType>::Type get(const ItemType& item) {
        return (item.*Getter)();
    }
};

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

    void insert(const ItemType& item) {
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

    void remove(const ItemType& item) {
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

    class iterator {
        public:
            iterator(
                RbTree* pTree,
                RbTreeNode* pNode)
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

            ItemType& operator*() {
                ASSERT(nullptr != mpNode);
                return NodeFinderType::fromNode(*mpNode);
            }

        private:

            RbTree* mpTree;
            RbTreeNode* mpNode;            
    };

    class const_iterator {
        public:
            const_iterator(
                const RbTree* pTree,
                const RbTreeNode* pNode)
                : mpTree(pTree)
                , mpNode(pNode) {
            }

            bool operator !=(const_iterator& rhs) {
                return mpNode != rhs.mpNode;
            }

            const_iterator& operator++() {
                ASSERT(nullptr != mpNode);
                mpNode = mpTree->mTree.getNext(mpNode);
                return *this;
            }

            ItemType& operator*() {
                ASSERT(nullptr != mpNode);
                return NodeFinderType::fromNode(*mpNode);
            }

        private:
            
            const RbTree* mpTree;
            const RbTreeNode* mpNode;

    };

    iterator begin() {
        return iterator(this, mTree.getFirst());
    }

    iterator end() {
        return iterator(this, nullptr);
    }

    const_iterator begin() const {
        return const_iterator(this, mTree.getFirst());
    }

    const_iterator end() const {
        return const_iterator(this, nullptr);
    }

private:

    RbTreeBase mTree;
};
