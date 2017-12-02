#include "core/serialize/Serializer.hpp"

#include "core/meta/MetaSystem.hpp"

Result metaSystemLoad(
	const std::type_info& typeInfo,
	void* pObject,
	ObjectReadStream& readStream)
{
	MetaType* pType = nullptr;
	Result r = Meta::get().findType(pType,typeInfo);
	if( r.peekFailed()) {
		return r;
	}

	return pType->load(pObject, readStream);	
}

Result metaSystemSave(
	const std::type_info& typeInfo,
	const void* pObject,
	ObjectWriteStream& writeStream)
{
	MetaType* pType = nullptr;
	Result r = Meta::get().findType(pType,typeInfo);
	if(r.peekFailed()) {
		return r;
	}
	
	return pType->save(pObject, writeStream);
}