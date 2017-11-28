#include "core/meta/MetaClass.hpp"
#include "core/meta/Meta.hpp"
#include "core/debug.hpp"

MetaClassBase::MetaClassBase(CStrArg name)
	: MetaType(name)
{
}

MetaClassProperty::MetaClassProperty(
	MetaClassBase* pMetaClassBase,
	MetaType* pPropertyType,
	CStrArg name)
	: mName(name)
	, mpPropertyType(pPropertyType)
	, mTreeNode(this)
{
	ASSERT(nullptr != pMetaClassBase);
	ASSERT(nullptr != pPropertyType);
	
	pMetaClassBase->addProperty(this);
}

Result MetaClassBase::load(void* object, const Json& json) const
{
	if(!json.IsObject() ) {
		return Result::makeFailureWithStringLiteral("Not a class");
	}

	for(auto&& property : mProperties) {
		auto pProperty = property->mItem;
		// TODO: evil std::string constructor here.
		const char* pPropertyName = pProperty->getName().c_str();


		Json propertyJson = json[pPropertyName];

		if(propertyJson.IsNull()) {

			LogFmt("Load property (Not Found):'%s'\n", pPropertyName);		

			continue;
		}

		LogFmt("Load property:%s\n", pPropertyName);		

		Result r = pProperty->load(object, propertyJson);
		if (r.peekFailed()) {
			return r;
		}

	}

	return Result::makeSuccess();
}

Result MetaClassBase::save(const void* pVoidObject, Json& json) const
{
	json = Json(make_ref<JsonObject>());

	for(auto&& property : mProperties) {
		auto pProperty = property->mItem;
		Json propertyJson;
		Result r = pProperty->save(pVoidObject, propertyJson);

		if( r.peekFailed()) {
			return r;
		}

		json.SetValueForKey(std::string(pProperty->getName().c_str()), propertyJson);
	}

	return Result::makeSuccess();
}


