#pragma once

#include "ui/ui.hpp"
#include <vector>

class Element
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
		std::vector<Element*> mChildren;
};


inline const Rect& Element::getRect() const
{
	return mRect;
}

inline void Element::setRect(const Rect& rect)
{
	mRect = rect;
}