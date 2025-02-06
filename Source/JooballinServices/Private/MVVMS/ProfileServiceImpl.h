// License Copyright (c) 2025 Eric Friedman

#pragma once

// Includes
// -------------------------------------
#include "MVVMS/ProfileService.h"

// Forward Declarations
// -------------------------------------
class IProfileRepo;

/**
 * Simple implementation of IProfileService that uses a profile repository to load a profile.
 */
class FProfileServiceImpl final : public IProfileService
{
public:
	explicit FProfileServiceImpl(const TSharedRef<IProfileRepo>& InProfileRepo);

protected:
	//~ Begin IProfileService Interface
	virtual TFuture<FProfile> GetProfileAsync() const override;
	//~ End IProfileService Interface
	
private:
	TSharedRef<IProfileRepo> ProfileRepo;
};
