// License Copyright (c) 2024 Eric Friedman

#pragma once

// Forward Declarations
// -------------------------------------
struct FProfile;

/**
 * 
 */
class IProfileService
{
public:
	virtual ~IProfileService() = default;

	virtual TFuture<FProfile> GetProfileAsync() const = 0;
};
Expose_TNameOf(IProfileService);