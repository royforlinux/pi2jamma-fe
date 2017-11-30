#include "Pi2Jamma/Configuration/KeyConfiguration.hpp"

void KeyConfiguration::initialize()
{
	META_CLASS(KeyConfiguration);
	META_CLASS_PROPERTY(KeyConfiguration, Up);
	META_CLASS_PROPERTY(KeyConfiguration, Down);	
	META_CLASS_PROPERTY(KeyConfiguration, Left);
	META_CLASS_PROPERTY(KeyConfiguration, Right);
	META_CLASS_PROPERTY(KeyConfiguration, Select);
	META_CLASS_PROPERTY(KeyConfiguration, Back);
}

KeyConfiguration::KeyConfiguration()
	: mUp(Key::UpArrow)
	, mDown(Key::DownArrow)
	, mLeft(Key::LeftArrow)
	, mRight(Key::RightArrow)
	, mSelect(Key::Space)
	, mBack(Key::Escape)
{}
