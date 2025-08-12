// License Copyright (c) 2025 Eric Friedman

#pragma once

// Includes
// -------------------------------------
#include "Profile.h"

/**
 * Interface for a simple profile repository.
 */
class IProfileRepo
{
public:
	virtual ~IProfileRepo() = default;
	
	virtual TFuture<FProfile> GetProfileAsync() const = 0;
};
Expose_TNameOf(IProfileRepo);