#include "ui/elements/Element.hpp"

Element::Element(Element* pParent, const Rect& rect)
	: mpParent(pParent)
	, mRect(rect)
	, mListNode(this)
{
	if(mpParent) {
		mpParent->mChildren.insertTail(&mListNode);
	}
}


void Element::setRect(const Rect& rect)
{
	auto oldSize = mRect.getSize();

	mRect = rect;
	
	resize(oldSize, mRect.getSize());
}

Element::~Element()
{
	if(mpParent) {
		mpParent->mChildren.remove(&mListNode);
	}
}

void Element::renderTree(RenderContext& renderContext)
{
	render(renderContext);

	#ifdef DEBUG_ELEMENT
		renderContext.drawRect(
			getRect(),
			Color(0x80, 0x80, 0x80, 0x80) );
	#endif

	
	for(auto && child : mChildren) {
		child->render(renderContext);
	}
}
