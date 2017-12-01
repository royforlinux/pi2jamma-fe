#pragma once

#include "core/container/Container.hpp"

#include "debug.hpp"

class DlListBase;

class DlListNode
{
public:

	DlListNode()
	#ifdef DEBUG_CONTAINER
		: mpList(nullptr)
	#endif	
	{
	}

	DlListNode(const DlListNode& rhs) = delete;
	DlListNode& operator=(const DlListNode& rhs) = delete;

	~DlListNode()
	{
		#ifdef DEBUG_CONTAINER
			ASSERT(nullptr == mpList);
		#endif
	}

private:

	DlListNode* mpNext = nullptr;
	DlListNode* mpPrev = nullptr;

	#ifdef DEBUG_CONTAINER
		DlListBase* mpList = nullptr;
	#endif

friend class DlListBase;

};	

class DlListBase final
{
public:
	DlListBase();
	~DlListBase();

	void abandon();

	void insertHead(DlListNode* pNode);
	void insertTail(DlListNode* pNode);
	void remove(DlListNode* pNode);

	DlListNode* getHead();
	const DlListNode* getHead() const;

	DlListNode* getTail();
	const DlListNode* getTail() const;

	DlListNode* getNext(DlListNode* pPrev);
	const DlListNode* getNext(const DlListNode* pPrev) const;

	DlListNode* getPrev(DlListNode* pNext);	
	const DlListNode* getPrev(const DlListNode* pNext) const;

private:
	DlListNode* mpHead;
	DlListNode* mpTail;
};

inline DlListBase::DlListBase()
	: mpHead(nullptr)
	, mpTail(nullptr)
{
}

inline DlListBase::~DlListBase()
{
	abandon();	
}

inline void DlListBase::abandon()
{
	#ifdef DEBUG_CONTAINER
		DlListNode* pS = getHead();
		while(nullptr != pS) 
		{
			pS->mpList = nullptr;
			pS = getNext(pS);
		}
	#endif

	mpHead = nullptr;
	mpTail = nullptr;
}

inline void DlListBase::insertTail(DlListNode* pNode)
{
	#ifdef DEBUG_CONTAINER
		ASSERT(nullptr == pNode->mpList);
		pNode->mpList = this;
	#endif

	pNode->mpNext = nullptr;
	pNode->mpPrev = mpTail;

	if(nullptr == mpTail)
	{
		mpHead = pNode;
	}
	else
	{
		mpTail->mpNext = pNode;		
	}

	mpTail = pNode;
}

inline void DlListBase::remove(DlListNode* pNode)
{
	#ifdef DEBUG_CONTAINER
		ASSERT(this == pNode->mpList);
		pNode->mpList = nullptr;
	#endif

	if(nullptr != pNode->mpNext)
	{
		pNode->mpNext->mpPrev = pNode->mpPrev;
	}
	else
	{
		mpTail = pNode->mpPrev;
	}

	if(nullptr != pNode->mpPrev)
	{
		pNode->mpPrev->mpNext = pNode->mpNext;
	}
	else
	{
		mpHead = pNode->mpNext;
	}
}

inline DlListNode* DlListBase::getHead()
{
	return mpHead;
}

inline const DlListNode* DlListBase::getHead() const
{
	return mpHead;
}

inline DlListNode* DlListBase::getTail()
{
	return mpTail;
}

inline const DlListNode* DlListBase::getTail() const
{
	return mpTail;
}

inline const DlListNode* DlListBase::getNext(const DlListNode* pPrev) const
{
	ASSERT(nullptr != pPrev);
	return pPrev->mpNext;
}

inline DlListNode* DlListBase::getNext(DlListNode* pPrev)
{
	ASSERT(nullptr != pPrev);
	return pPrev->mpNext;
}

inline DlListNode* DlListBase::getPrev(DlListNode* pNext)
{
	ASSERT(nullptr != pNext);
	return pNext->mpPrev;
}

inline const DlListNode* DlListBase::getPrev(const DlListNode* pNext) const
{
	ASSERT(nullptr != pNext);
	return pNext->mpPrev;
}