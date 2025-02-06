// License Copyright (c) 2025 Eric Friedman

#pragma once

// Forward Declarations
// -------------------------------------
struct FProfile;

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