// License Copyright (c) 2024 Eric Friedman

#pragma once

// Includes
// -------------------------------------
#include "MVVMS/ProfileRepo.h"


/**
 * 
 */
class FProfileRepoImpl final : public IProfileRepo
{
public:
	FProfileRepoImpl();

protected:
	//~ Begin IProfileRepo Interface
	virtual TFuture<FProfile> GetProfile() const override;
	//~ End IProfileRepo Interface

private:
	const FString ProfileFilePath;
};
