// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "ProfileServiceImpl.h"

#include "MVVMS/ProfileRepo.h"

// CONSTRUCTOR
// -------------------------------------
FProfileServiceImpl::FProfileServiceImpl(const TSharedRef<IProfileRepo>& InProfileRepo)
	: ProfileRepo(InProfileRepo)
{
}

// GetProfileAsync
// -------------------------------------
/*virtual*/ TFuture<FProfile> FProfileServiceImpl::GetProfileAsync() const
{
	return ProfileRepo->GetProfileAsync();
}
