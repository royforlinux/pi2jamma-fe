#include "Pi2Jamma/Configuration/Configuration.hpp"

#include "core/meta/Meta.hpp"

void Configuration::initialize()
{
	KeyConfiguration::initialize();

	META_CLASS(Configuration);
	META_CLASS_PROPERTY(Configuration, SaveConfigOnExit);
	META_CLASS_PROPERTY(Configuration, Keys);
}


Configuration::Configuration()
	: mSaveConfigOnExit(true)
{}