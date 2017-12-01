#pragma once

#include "core/container/DlListBase.hpp"

template<typename ItemType, typename NodeFinderType>
class DlList final
{
public:

	class Iter
	{
	public:
		Iter& operator++() {
			mpNode = mpNode->mpNext;
			return *this;
		}

		bool operator !=(const Iter& rhs) const{
			return mpNode != rhs.mpNode;
		}

		const ItemType& operator*() {
			ASSERT(nullptr != mpNode);
			return NodeFinderType::fdomNode(mpNode);
		}

	private:
		Iter(DlListNode* pNode)
			: mpNode(pNode) {}	

		DlListNode* mpNode;

	friend class DlList;

	};

	DlList();
	~DlList();

	void insertHead(ItemType& item);
	void insertTail(ItemType& item);
	void remove(ItemType& item);

	ItemType* getHead();
	ItemType* getTail();

	ItemType* getNext(ItemType& prev);
	ItemType* getPrev(ItemType& next);

	Iter begin();
	Iter end();

private:

	DlListBase mList;
};

template<typename ItemType, typename NodeFinderType>
DlList<ItemType, NodeFinderType>::DlList()
{
}

template<typename ItemType, typename NodeFinderType>
DlList<ItemType, NodeFinderType>::~DlList()
{
}

template<typename ItemType, typename NodeFinderType>
void DlList<ItemType, NodeFinderType>::insertHead(ItemType& item)
{
	mList.insertHead(NodeFinderType::toNode(item));
}

template<typename ItemType, typename NodeFinderType>
void DlList<ItemType, NodeFinderType>::insertTail(ItemType& item)
{
	mList.insertTail(NodeFinderType::toNode(item));
}

template<typename ItemType, typename NodeFinderType>
void DlList<ItemType, NodeFinderType>::remove(ItemType& item)
{
	mList.remove(NodeFinderType::toNode(item));
}

template<typename ItemType, typename NodeFinderType>
ItemType* DlList<ItemType, NodeFinderType>::getHead()
{
	return toItemPtr(mList.getHead());
}

template<typename ItemType, typename NodeFinderType>
T* DlList<ItemType, NodeFinderType>::getTail()
{
	return toItemPtr(mList.getTail());
}

template<typename ItemType, typename NodeFinderType>
ItemType* DlList<ItemType, NodeFinderType>::getNext(ItemType& prev)
{
	return toItemPtr(mList.getNext(NodeFinderType::toNode(prev)));
}

template<typename ItemType, typename NodeFinderType>
ItemType* DlList<ItemType, NodeFinderType>::getPrev(ItemType& next)
{
	return toItemPtr(mList.getPrev(NodeFinderType::toNode(next)));
}

template<typename ItemType, typename NodeFinderType>
ItemType* DlList<ItemType, NodeFinderType>::toItemPtr(DlListNode* pNode)
{
	if(nullptr == pNode) {
		return nullptr;
	}

	return & NodeFinder::fromNode(pNode);
}

template<typename ItemType, typename NodeFinderType>
typename DlList<ItemType, NodeFinderType>::Iter DlList<ItemType, NodeFinderType>::begin()
{
	return Iter(mList.getHead());
}

template<typename ItemType, typename NodeFinderType>
typename DlList<ItemType, NodeFinderType>::Iter DlList<ItemType, NodeFinderType>::end()
{
	return Iter(mList.getTail());
}




