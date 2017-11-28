#pragma once

#include "ui/ui.hpp"
#include "core/container/DlList.hpp"
#include "core/RefCounted.hpp"
#include <vector>

#define DEBUG_ELEMENT

class Element : public RefCounted
{
	public:

		Element(Element* pParent);

		virtual ~Element();

		const Rect& getRect() const;
		void setRect(const Rect& rect);

		UnitType getX() const;
		UnitType getY() const;

		void renderTree(RenderContext& renderContext);

	protected:

		virtual void render(RenderContext& renderContext) = 0;
		virtual void resize(const Size& oldSize, const Size& newSize) = 0;

	private:

		Rect mRect;
		Element* mpParent;

		using ListType = DlList<ref<Element>>;
		ListType mChildren;
		ListType::Node mListNode;
};

inline const Rect& Element::getRect() const
{
	return mRect;
}

inline UnitType Element::getX() const
{
	return mRect.getX();
}

inline UnitType Element::getY() const
{
	return mRect.getY();
}