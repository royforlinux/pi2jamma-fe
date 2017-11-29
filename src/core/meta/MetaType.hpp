#pragma once

#include "core/RefCounted.hpp"
#include "core/Result.hpp"
#include "core/StringUtil.hpp"

#include "core/container/RbTree.hpp"
#include "core/json/Json.hpp"

class MetaType
{
public:
	MetaType(CStr name, const std::type_info& typeInfo);
	virtual ~MetaType();

	CStr getName(void) const {
		return mName;
	}

 	const std::type_info& getTypeInfo() const {
 		return mTypeInfo;
 	}

	virtual Result load(void* pItem, const Json& fson) const = 0;
	virtual Result save(const void* pItem, Json& json) const = 0;

protected:



private:

	CStr mName;
	const std::type_info& mTypeInfo;

public:

	RbTreeNode mByNameTreeNode;
	RbTreeNode mByTypeInfoTreeNode;		
};