// License Copyright (c) 2025 Eric Friedman

#pragma once

// Forward Declarations
// -------------------------------------
struct FProfile;

/**
 * Interface for a simple profile service.
 */
class IProfileService
{
public:
	virtual ~IProfileService() = default;

	virtual TFuture<FProfile> GetProfileAsync() const = 0;
};
Expose_TNameOf(IProfileService);