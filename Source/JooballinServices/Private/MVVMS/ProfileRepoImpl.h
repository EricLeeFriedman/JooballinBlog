// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// -------------------------------------
#include "MVVMS/ProfileRepo.h"


/**
 * Simple implementation of IProfileRepo that uses a json file to load a profile.
 */
class FProfileRepoImpl final : public IProfileRepo
{
public:
	FProfileRepoImpl();

protected:
	//~ Begin IProfileRepo Interface
	virtual TFuture<FProfile> GetProfileAsync() const override;
	//~ End IProfileRepo Interface

private:
	const FString ProfileFilePath;
};
