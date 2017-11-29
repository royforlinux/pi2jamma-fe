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
