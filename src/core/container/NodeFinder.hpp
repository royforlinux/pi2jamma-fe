#pragma once

template<
    typename ItemType,
    typename NodeType,
    NodeType ItemType::*Member >
struct NodeFinderField
{
    static size_t offset() {

        NodeType& member = ((ItemType*)(nullptr))->*Member;

        const size_t o =
            reinterpret_cast<char*>(&member)
                - reinterpret_cast<char*>((ItemType*)(nullptr));   

        return o;   
    }

    static const ItemType& fromNode(const NodeType& node) {
        return
            *reinterpret_cast<ItemType*>(
                const_cast<char*>(
                    reinterpret_cast<const char*>(&node) - offset()));
    }

    static ItemType& fromNode(NodeType& node) {
        return
            const_cast<ItemType&>(
                fromNode(const_cast<const NodeType&>(node)));
    }

    static const NodeType& toNode(const ItemType& itemType) {
        return *((NodeType*)(& (itemType.*Member)));
    }

    static NodeType& toNode(ItemType& item) {
        return
            const_cast<NodeType&>(
                toNode(const_cast<const ItemType&>(item)));
    }    
};