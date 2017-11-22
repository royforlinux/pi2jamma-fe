#include "ui/Element.hpp"
#include <algorithm>

Element::Element(Element* pParent)
	: mpParent(pParent)
{
	if(mpParent) {
		mpParent->mChildren.push_back(this);
	}
}

Element::~Element()
{
	if(mpParent) {
		mpParent->mChildren.erase(
			std::find(
				mpParent->mChildren.begin(),
				mpParent->mChildren.end(),
				this
			)
		);
	}
}

void Element::renderTree(RenderContext& renderContext)
{
	render(renderContext);
	
	for(Element* e : mChildren) {
		e->render(renderContext);
	}
}
