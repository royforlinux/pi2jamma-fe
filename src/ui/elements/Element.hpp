#pragma once

#include "core/container/DlList.hpp"
#include "ui/Rect.hpp"
#include "ui/RenderContext.hpp"
#include "ui/Size.hpp"

#include "core/RefCounted.hpp"

#define DEBUG_ELEMENT

namespace ui {

class Element : public RefCounted
{
	public:

		Element(Element* pParent, const Rect& rect);

		virtual ~Element();

		const Rect& getRect() const;
		void setRect(const Rect& rect);

		UnitType getX() const;
		UnitType getY() const;

		void renderTree(RenderContext& renderContext);

	protected:

		virtual void render(RenderContext& renderContext) = 0;
		virtual void resize(const Size& oldSize, const Size& newSize) {}

	private:
		
		Element* mpParent;
		Rect mRect;
		DlListNode mListNode;

		using ListType =
			DlList<
				Element,
				NodeFinderField<
					Element,
					DlListNode,
					& Element::mListNode>>;

		ListType mChildren;
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

}