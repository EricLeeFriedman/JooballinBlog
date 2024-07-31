﻿// License Copyright (c) 2024 Eric Friedman

#pragma once

// Forward Declarations
// -------------------------------------
struct FProfile;

/**
 * Interface for a simple profile repository interface.
 */
class IProfileRepo
{
public:
	virtual ~IProfileRepo() = default;
	
	virtual TFuture<FProfile> GetProfileAsync() const = 0;
};
Expose_TNameOf(IProfileRepo);