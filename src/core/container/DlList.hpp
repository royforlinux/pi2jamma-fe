#pragma once

#include "core/container/DlListBase.hpp"
#include "core/container/NodeFinder.hpp"

template<typename ItemType, typename NodeFinderType>
class DlList final
{
public:

	template<
		typename ListType,
		typename IteratorItemType,
		typename NodeType>
	class Iterator
	{
	public:
		Iterator& operator++() {
			mpNode = mpList->mList.getNext(mpNode);
			return *this;
		}

		bool operator !=(const Iterator& rhs) const{
			return mpNode != rhs.mpNode;
		}

		IteratorItemType& operator*() {
			ASSERT(nullptr != mpNode);
			return NodeFinderType::fromNode(*mpNode);
		}

	private:
		Iterator(ListType* pList, NodeType* pNode)
			: mpList(pList)
			, mpNode(pNode) {}	

		ListType* mpList;
		NodeType* mpNode;

	friend class DlList;

	};

	using ConstIterator = Iterator<const DlList, const ItemType, const DlListNode >;
	using NonConstIterator = Iterator<DlList, ItemType, DlListNode >;

	DlList();
	~DlList();

	void insertHead(ItemType& item);
	void insertTail(ItemType& item);
	void remove(ItemType& item);

	ItemType* getHead();
	const ItemType* getHead() const;

	ItemType* getTail();
	const ItemType* getTail() const;

	ItemType* getNext(ItemType& prev);
	const ItemType* getNext(const ItemType& prev) const;

	ItemType* getPrev(ItemType& next);
	const ItemType* getPrev(const ItemType& next) const;

	ConstIterator begin() const;
	ConstIterator end() const;

	NonConstIterator begin();
	NonConstIterator end();	

private:

	ItemType* toItemPtr(DlListNode* pNode);
	const ItemType* toItemPtr(const DlListNode* pNode) const;
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
	mList.insertHead(&NodeFinderType::toNode(item));
}

template<typename ItemType, typename NodeFinderType>
void DlList<ItemType, NodeFinderType>::insertTail(ItemType& item)
{
	mList.insertTail(&NodeFinderType::toNode(item));
}

template<typename ItemType, typename NodeFinderType>
void DlList<ItemType, NodeFinderType>::remove(ItemType& item)
{
	mList.remove(&NodeFinderType::toNode(item));
}

template<typename ItemType, typename NodeFinderType>
const ItemType* DlList<ItemType, NodeFinderType>::getHead() const
{
	return toItemPtr(mList.getHead());
}

template<typename ItemType, typename NodeFinderType>
ItemType* DlList<ItemType, NodeFinderType>::getHead()
{
	return toItemPtr(mList.getHead());
}

template<typename ItemType, typename NodeFinderType>
const ItemType* DlList<ItemType, NodeFinderType>::getTail() const
{
	return toItemPtr(mList.getTail());
}

template<typename ItemType, typename NodeFinderType>
ItemType* DlList<ItemType, NodeFinderType>::getTail()
{
	return toItemPtr(mList.getTail());
}

template<typename ItemType, typename NodeFinderType>
const ItemType* DlList<ItemType, NodeFinderType>::getNext(const ItemType& prev) const
{
	return toItemPtr(mList.getNext(&NodeFinderType::toNode(prev)));
}

template<typename ItemType, typename NodeFinderType>
ItemType* DlList<ItemType, NodeFinderType>::getNext(ItemType& prev)
{
	return toItemPtr(mList.getNext(&NodeFinderType::toNode(prev)));
}

template<typename ItemType, typename NodeFinderType>
const ItemType* DlList<ItemType, NodeFinderType>::getPrev(const ItemType& next) const
{
	return toItemPtr(mList.getPrev(&NodeFinderType::toNode(next)));
}

template<typename ItemType, typename NodeFinderType>
ItemType* DlList<ItemType, NodeFinderType>::getPrev(ItemType& next)
{
	return toItemPtr(mList.getPrev(&NodeFinderType::toNode(next)));
}

template<typename ItemType, typename NodeFinderType>
const ItemType* DlList<ItemType, NodeFinderType>::toItemPtr(const DlListNode* pNode) const
{
	if(nullptr == pNode) {
		return nullptr;
	}

	return & NodeFinderType::fromNode(pNode);
}

template<typename ItemType, typename NodeFinderType>
ItemType* DlList<ItemType, NodeFinderType>::toItemPtr(DlListNode* pNode)
{
	if(nullptr == pNode) {
		return nullptr;
	}

	return & NodeFinderType::fromNode(pNode);
}

template<typename ItemType, typename NodeFinderType>
typename DlList<ItemType, NodeFinderType>::NonConstIterator DlList<ItemType, NodeFinderType>::begin()
{
	return NonConstIterator(this, mList.getHead());
}

template<typename ItemType, typename NodeFinderType>
typename DlList<ItemType, NodeFinderType>::NonConstIterator DlList<ItemType, NodeFinderType>::end()
{
	return NonConstIterator(this, nullptr);
}

template<typename ItemType, typename NodeFinderType>
typename DlList<ItemType, NodeFinderType>::ConstIterator DlList<ItemType, NodeFinderType>::begin() const
{
	return ConstIterator(this, mList.getHead());
}

template<typename ItemType, typename NodeFinderType>
typename DlList<ItemType, NodeFinderType>::ConstIterator DlList<ItemType, NodeFinderType>::end() const
{
	return ConstIterator(this, nullptr);
}





