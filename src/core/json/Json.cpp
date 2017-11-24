
#include "core/json/Json.hpp"

JsonBase::Ref JsonBase::GetValueForKey( Arg< String >::Type key )
{
    return make_ref<JsonNull>();
}

void JsonBase::SetValueForKey(
	Arg< String >::Type key,
    Arg< JsonBase::Ref >::Type refJson )
{
};

void JsonBase::SetIntegerValueForKey(
	Arg< String >::Type key,
    Arg< JsonIntType >::Type val )
{
}

void JsonBase::SetStringValueForKey(
	Arg< String >::Type key,
    Arg< String >::Type val )
{
}

