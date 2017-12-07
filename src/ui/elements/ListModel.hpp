#pragma once

#include "core/RefCounted.hpp"

namespace ui {

template<typename ElementType>
class ListModel : public RefCounted
{
public:
	virtual ~ListModel() = default;

	virtual size_t getNumItems() const = 0;
	virtual ElementType getItem(size_t index) const = 0;
	virtual void onItemHighlighted(size_t newSelection) = 0;
	virtual void onItemSelected(size_t newSelection) = 0;

};

}