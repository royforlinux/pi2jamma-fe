#pragma once

#include "core/String.hpp"
#include "json/Json.hpp"

class LoadTextContext
{
public:
	LoadTextContext(ref<Json> refJson)
		: mrefJson(std::move(refJson)) {
	}

	const ref<Json>& getJson() {
		return mrefJson;
	}

private:
	ref<Json> mrefJson;
};