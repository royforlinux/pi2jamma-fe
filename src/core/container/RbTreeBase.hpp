#pragma once

#include <functional>
#include "core/container/Container.hpp"
#include "core/debug.hpp"

class RbTreeNodeBase
{
public:
    #ifdef DEBUG_CONTAINER

        RbTreeNodeBase() {
            mpTree = nullptr;
        }

        ~RbTreeNodeBase() {
            ASSERT(nullptr == mpTree);
        }

    #endif

    RbTreeNodeBase(const RbTreeNodeBase& rhs) = delete;
    RbTreeNodeBase& operator=(const RbTreeNodeBase& rhs) = delete;

    mutable RbTreeNodeBase* mpLeft;
    mutable RbTreeNodeBase* mpRight;
    mutable RbTreeNodeBase* mpParent;

    mutable size_t mRed;    

    #ifdef DEBUG_CONTAINER
        mutable void* mpTree;
    #endif

};

class RbTreeBase
{
public:

	RbTreeBase();
	~RbTreeBase();
	

	using InsertFunction = const std::function<int(const RbTreeNodeBase*, const RbTreeNodeBase*)>;
	using CompareFunction = const std::function<int(const RbTreeNodeBase*)>;

	void clear();
	void insert(RbTreeNodeBase* pTreeNode, const InsertFunction& insrtFunction);
	void remove(RbTreeNodeBase* pTreeNode);

	RbTreeNodeBase* find(const CompareFunction& compare);
	const RbTreeNodeBase* find(const CompareFunction& compare) const;

    const RbTreeNodeBase* findClosest(const CompareFunction& compare) const;
    RbTreeNodeBase* findClosest(const CompareFunction& compare);

	RbTreeNodeBase* getFirst();
	const RbTreeNodeBase* getFirst() const;

	RbTreeNodeBase* getNext(RbTreeNodeBase* pPrev);
	const RbTreeNodeBase* getNext(const RbTreeNodeBase* pPrev) const;

	const RbTreeNodeBase* getLast() const;
	RbTreeNodeBase* getLast();

	const RbTreeNodeBase* getPrev(const RbTreeNodeBase* pNext) const;
	RbTreeNodeBase* getPrev(RbTreeNodeBase* pNext);

	size_t count() const;

	RbTreeNodeBase* findAt(size_t index);
	const RbTreeNodeBase* findAt(size_t index) const;

private:

	void reset();

	void insertHelp(RbTreeNodeBase* pZ, const InsertFunction& insertFunction);
	void removeFixUp(RbTreeNodeBase* pX);

	void leftRotate(RbTreeNodeBase* pX);
	void rightRotate(RbTreeNodeBase* pY);
	const RbTreeNodeBase* successor(const RbTreeNodeBase* pX) const;
	RbTreeNodeBase* successor(RbTreeNodeBase* pX);
	const RbTreeNodeBase* predecessor(const RbTreeNodeBase* pX) const;

    RbTreeNodeBase mRoot;
    RbTreeNodeBase mSentinal;	
};	
