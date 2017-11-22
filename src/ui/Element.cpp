#include "ui/Element.hpp"
#include <algorithm>

Element::Element(Element* pParent)
	: mpParent(pParent)
	, mListNode(this)
{
	if(mpParent) {
		mpParent->mChildren.insertTail(&mListNode);
	}
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
	
	for(auto && child : mChildren) {
		child->render(renderContext);
	}
}
