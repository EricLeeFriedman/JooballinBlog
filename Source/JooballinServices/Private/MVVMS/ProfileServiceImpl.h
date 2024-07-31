// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// -------------------------------------
#include "MVVMS/ProfileService.h"

// Forward Declarations
// -------------------------------------
class IProfileRepo;

/**
 * 
 */
class FProfileServiceImpl final : public IProfileService
{
public:
	explicit FProfileServiceImpl(const TSharedRef<IProfileRepo> InProfileRepo);

protected:
	//~ Begin IProfileService Interface
	virtual TFuture<FProfile> GetProfileAsync() const override;
	//~ End IProfileService Interface
	
private:
	TSharedRef<IProfileRepo> ProfileRepo;
};
