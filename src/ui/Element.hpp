#pragma once

#include "ui/ui.hpp"
#include "core/container/DlList.hpp"
#include "core/RefCounted.hpp"
#include <vector>

class Element : public RefCounted
{
	public:

		Element(Element* pParent);

		virtual ~Element();

		const Rect& getRect() const;
		void setRect(const Rect& rect);

		void renderTree(RenderContext& renderContext);

		virtual void render(RenderContext& renderContext) = 0;

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

inline void Element::setRect(const Rect& rect)
{
	mRect = rect;
}