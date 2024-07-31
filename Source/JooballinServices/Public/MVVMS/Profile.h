// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// --------------------------------------

// Engine
#include "Serialization/JsonSerializable.h"
#include "Serialization/JsonSerializerMacros.h"

/**
 * 
 */
struct FProfile final : FJsonSerializable
{
	FText Name;
	int32 Age = 0;
	FString Website;

	BEGIN_JSON_SERIALIZER
		JSON_SERIALIZE("Name", Name);
		JSON_SERIALIZE("Age", Age);
		JSON_SERIALIZE("Website", Website);
	END_JSON_SERIALIZER
};
