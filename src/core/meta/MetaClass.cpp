#include "core/meta/MetaClass.hpp"
#include "core/meta/Meta.hpp"
#include "core/debug.hpp"

MetaClassBase::MetaClassBase(CStrArg name, const std::type_info& typeInfo)
	: MetaType(name, typeInfo)
{
}

MetaClassProperty::MetaClassProperty(
	MetaClassBase* pMetaClassBase,
	MetaType* pPropertyType,
	CStrArg name)
	: mName(name)
	, mpPropertyType(pPropertyType)
	, mpMetaClassBase(pMetaClassBase)
{
	ASSERT(nullptr != pMetaClassBase);
	ASSERT(nullptr != pPropertyType);
	
	pMetaClassBase->addProperty(this);
}

MetaClassProperty::~MetaClassProperty()
{
	mpMetaClassBase->removeProperty(this);
}


Result MetaClassBase::load(void* object, const Json& json) const
{
	if(!json.IsObject() ) {
		return Result::makeFailureWithStringLiteral("Not a class");
	}

	for(auto&& prop : mProperties) {

		CStr propertyName = prop.getName();

		Json propertyJson = json[propertyName];

		if(propertyJson.IsNull()) {

			// LogFmt("Load property (Not Found):'%s'\n", pPropertyName);		

			continue;
		}

		// LogFmt("Load property:%s\n", pPropertyName);		

		Result r = prop.load(object, propertyJson);
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

		Json propertyJson;
		Result r = property.save(pVoidObject, propertyJson);

		if( r.peekFailed()) {
			return r;
		}

		json.SetValueForKey(std::string(property.getName().c_str()), propertyJson);
	}

	return Result::makeSuccess();
}


