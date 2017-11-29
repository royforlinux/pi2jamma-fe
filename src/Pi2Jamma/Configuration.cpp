#include "Pi2Jamma/Configuration.hpp"

void Configuration::initialize()
{
	META_CLASS(Configuration);
	META_CLASS_FIELD(Configuration, UpKey);
	META_CLASS_FIELD(Configuration, DownKey);	
	META_CLASS_FIELD(Configuration, LeftKey);
	META_CLASS_FIELD(Configuration, RightKey);
	META_CLASS_FIELD(Configuration, SelectKey);
	META_CLASS_FIELD(Configuration, BackKey);
	META_CLASS_FIELD(Configuration, SaveConfigOnExit);
}

Configuration::Configuration()
	: mUpKey(Key::UpArrow)
	, mDownKey(Key::DownArrow)
	, mLeftKey(Key::LeftArrow)
	, mRightKey(Key::RightArrow)
	, mSelectKey(Key::Space)
	, mBackKey(Key::Escape)
{}
