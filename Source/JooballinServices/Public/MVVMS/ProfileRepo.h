// License Copyright (c) 2024 Eric Friedman

#pragma once

// Forward Declarations
// -------------------------------------
struct FProfile;

/**
 * 
 */
class IProfileRepo
{
public:
	virtual ~IProfileRepo() = default;
	
	virtual TFuture<FProfile> GetProfile() const = 0;
};
Expose_TNameOf(IProfileRepo);