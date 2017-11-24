#pragma once

#include "core/RefCounted.hpp"


#include "core/result.hpp"
#include "core/String.hpp"
#include "core/container/RbTree.hpp"
#include "core/json/Json.hpp"

class MetaType
{
public:
	MetaType(CStr name);

	virtual ~MetaType() = default;

	const CStr& getName(void) const {
		return mName;
	}

	virtual const std::type_info& getTypeInfo() const = 0;	
	virtual Result load(void* pItem, const Json& refJson) = 0;

protected:



private:

	CStr mName;

public:

	RbTreeNode<MetaType*> mByNameTreeNode;
	RbTreeNode<MetaType*> mByTypeInfoTreeNode;		
};