#pragma once

#include "debug.hpp"

template<typename T>
class DlList final
{
public:

	class Node
	{
	public:

		Node(const T& object)
			: mObject(object)
		{
		}

		Node(T&& object)
			: mObject(std::move(object))
		{
		}

		~Node()
		{
			#ifdef DEBUG_CONTAINER
				ASSERT(nullptr == mpParent);
			#endif
		}

	const T& get() { return mObject; }

	private:

		Node* mpNext = nullptr;
		Node* mpPrev = nullptr;
		T mObject;

		#ifdef DEBUG_CONTAINER
			DlList* mpParent = nullptr;
		#endif

	friend class DlList;

	};	

	class Iter
	{
	public:
		Iter& operator++()
		{
			mpNode = mpNode->mpNext;
			return *this;
		}

		bool operator !=(const Iter& rhs) const{
			return mpNode != rhs.mpNode;
		}

		const T& operator*() {
			return mpNode->get();
		}

	private:
		Iter(Node* pNode)
			: mpNode(pNode) {}		
		Node* mpNode;

	friend class DlList;

	};

	DlList();
	~DlList();

	void insertHead(Node* pNode);
	void insertTail(Node* pNode);
	void remove(Node* pNode);

	Node* getHead();
	Node* getTail();

	Node* getNext(Node* pPrev);
	Node* getPrev(Node* pNext);

	Iter begin();
	Iter end();


private:

	Node* mpHead;
	Node* mpTail;
};

template<typename T>
DlList<T>::DlList()
	: mpHead(nullptr)
	, mpTail(nullptr)
{
}

template<typename T>
DlList<T>::~DlList()
{
	ASSERT(mpHead == nullptr);
}

template<typename T>
void DlList<T>::insertHead(Node* pNode)
{
	#ifdef DEBUG_CONTAINER
		ASSERT(nullptr == pNode->mpParent);
		pNode->mpParent = this;
	#endif

	pNode->mpNext = mpHead;
	pNode->mpPrev = nullptr;

	if(nullptr == mpHead)
	{
		mpTail = pNode;
	}	
	else
	{
		mpHead->mpPrev = pNode;
	}

	mpHead = pNode;
}

template<typename T>
void DlList<T>::insertTail(Node* pNode)
{
	#ifdef DEBUG_CONTAINER
		ASSERT(nullptr == pNode->mpParent);
		pNode->mpParent = this;
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

template<typename T>
void DlList<T>::remove(Node* pNode)
{
	#ifdef DEBUG_CONTAINER
		ASSERT(this == pNode->mpParent);
		pNode->mpParent = nullptr;
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

template<typename T>
typename DlList<T>::Node* DlList<T>::getHead()
{
	return mpHead;
}

template<typename T>
typename DlList<T>::Node* DlList<T>::getTail()
{
	return mpTail;
}

template<typename T>
typename DlList<T>::Node* DlList<T>::getNext(Node* pPrev)
{
	ASSERT(nullptr != pPrev);
	return pPrev->mpNext;
}

template<typename T>
typename DlList<T>::Node* DlList<T>::getPrev(Node* pNext)
{
	ASSERT(nullptr != pNext);
	return pNext->mpPrev;
}

template<typename T>
typename DlList<T>::Iter DlList<T>::begin()
{
	return Iter(mpHead);
}

template<typename T>
typename DlList<T>::Iter DlList<T>::end()
{
	return Iter(mpTail);
}


