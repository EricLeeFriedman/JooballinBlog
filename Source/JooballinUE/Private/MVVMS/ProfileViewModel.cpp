// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "ProfileViewModel.h"

#include "JooballinServices.h"
#include "MVVMS/Profile.h"
#include "MVVMS/ProfileService.h"

// LoadProfile
// -------------------------------------
void UProfileViewModel::LoadProfile()
{
	UE_MVVM_SET_PROPERTY_VALUE(bIsProfileLoading, true);
	const TSharedRef<IProfileService> ProfileService = GetService<IProfileService>();
	ProfileService->GetProfileAsync().Next([this](const FProfile& Profile)
	{
		AsyncTask(ENamedThreads::GameThread, [this, Profile]()
		{
			UE_MVVM_SET_PROPERTY_VALUE(Name, Profile.Name);
			UE_MVVM_SET_PROPERTY_VALUE(Age, Profile.Age);
			UE_MVVM_SET_PROPERTY_VALUE(Website, Profile.Website);
			UE_MVVM_SET_PROPERTY_VALUE(bIsProfileLoading, false);
		});
	});
}
