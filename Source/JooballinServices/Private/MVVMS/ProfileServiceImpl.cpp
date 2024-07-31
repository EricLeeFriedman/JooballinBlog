// License Copyright (c) 2024 Eric Friedman

// Includes
// -------------------------------------
#include "ProfileServiceImpl.h"

#include "MVVMS/ProfileRepo.h"

// CONSTRUCTOR
// -------------------------------------
FProfileServiceImpl::FProfileServiceImpl(const TSharedRef<IProfileRepo> InProfileRepo)
	: ProfileRepo(InProfileRepo)
{
}

// GetProfile
// -------------------------------------
/*virtual*/ TFuture<FProfile> FProfileServiceImpl::GetProfileAsync() const
{
	return ProfileRepo->GetProfile();
}
