#pragma once

#include <functional>
#include "core/container/Container.hpp"
#include "core/debug.hpp"

class RbTreeNode
{
public:
    #ifdef DEBUG_CONTAINER

        RbTreeNode() {
            mpTree = nullptr;
        }

        ~RbTreeNode() {
            ASSERT(nullptr == mpTree);
        }

    #endif

    RbTreeNode(const RbTreeNode& rhs) = delete;
    RbTreeNode& operator=(const RbTreeNode& rhs) = delete;

    mutable RbTreeNode* mpLeft;
    mutable RbTreeNode* mpRight;
    mutable RbTreeNode* mpParent;

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

	using InsertFunction = const std::function<int(const RbTreeNode*, const RbTreeNode*)>;
	using CompareFunction = const std::function<int(const RbTreeNode*)>;

	void clear();
	void insert(RbTreeNode* pTreeNode, const InsertFunction& insrtFunction);
	void remove(RbTreeNode* pTreeNode);

	RbTreeNode* find(const CompareFunction& compare);
	const RbTreeNode* find(const CompareFunction& compare) const;

    const RbTreeNode* findClosest(const CompareFunction& compare) const;
    RbTreeNode* findClosest(const CompareFunction& compare);

	RbTreeNode* getFirst();
	const RbTreeNode* getFirst() const;

	RbTreeNode* getNext(RbTreeNode* pPrev);
	const RbTreeNode* getNext(const RbTreeNode* pPrev) const;

	const RbTreeNode* getLast() const;
	RbTreeNode* getLast();

	const RbTreeNode* getPrev(const RbTreeNode* pNext) const;
	RbTreeNode* getPrev(RbTreeNode* pNext);

	size_t count() const;

	RbTreeNode* findAt(size_t index);
	const RbTreeNode* findAt(size_t index) const;

private:

	void reset();

	void insertHelp(RbTreeNode* pZ, const InsertFunction& insertFunction);
	void removeFixUp(RbTreeNode* pX);

	void leftRotate(RbTreeNode* pX);
	void rightRotate(RbTreeNode* pY);
	const RbTreeNode* successor(const RbTreeNode* pX) const;
	RbTreeNode* successor(RbTreeNode* pX);
	const RbTreeNode* predecessor(const RbTreeNode* pX) const;

    RbTreeNode mRoot;
    RbTreeNode mSentinal;	
};	
