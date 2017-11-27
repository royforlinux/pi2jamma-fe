
#include "core/json/Json.hpp"

JsonBase::Ref JsonBase::GetValueForKey( Arg< std::string >::Type key )
{
    return make_ref<JsonNull>();
}

void JsonBase::SetValueForKey(
	Arg< std::string >::Type key,
    Arg< JsonBase::Ref >::Type refJson )
{
};

void JsonBase::SetIntegerValueForKey(
	Arg< std::string >::Type key,
    Arg< JsonIntType >::Type val )
{
}

void JsonBase::SetStringValueForKey(
	Arg< std::string >::Type key,
    Arg< std::string >::Type val )
{
}

