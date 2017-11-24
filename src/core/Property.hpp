#pragma once

#include "core/Arg.hpp"

#define PROPERTY(PropType, Name) \
	public: \
		typename Arg<PropType>::Type get##Name() const { return m##Name; } \
		void set##Name(typename Arg<PropType>::Type v) { m##Name = v; } \
		PropType m##Name;
