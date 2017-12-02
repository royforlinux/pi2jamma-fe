#pragma once

#include "core/RefCounted.hpp"
#include "core/Result.hpp"
#include "core/StringUtil.hpp"

#include "core/container/RbTree.hpp"
#include "core/serialize/ObjectReadStream.hpp"
#include "core/serialize/ObjectWriteStream.hpp"

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

	virtual Result load(void* pItem, ObjectReadStream& readStream) const = 0;
	virtual Result save(const void* pItem, ObjectWriteStream& writeStream) const = 0;

private:

	CStr mName;
	const std::type_info& mTypeInfo;

public:

	RbTreeNode mByNameTreeNode;
	RbTreeNode mByTypeInfoTreeNode;		
};