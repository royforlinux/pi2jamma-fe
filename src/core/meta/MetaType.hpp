#pragma once

#include "core/RefCounted.hpp"

class MetaType : public RefCounted
{
public:
	MetaType(const char* pName)
		: mpName(pName) {

	}

	virtual ~MetaType() = default;

	const char* getName(void) const {
		return mpName;
	}

private:

	const char* mpName;
};