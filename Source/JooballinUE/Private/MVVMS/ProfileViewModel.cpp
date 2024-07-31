// License Copyright (c) 2024 Eric Friedman

// Includes
// -------------------------------------
#include "ProfileViewModel.h"

#include "JooballinServices.h"
#include "MVVMS/Profile.h"
#include "MVVMS/ProfileService.h"

// CONSTRUCTOR
// -------------------------------------
UProfileViewModel::UProfileViewModel()
	: ProfileService(FJooballinServicesModule::GetTypeContainer().GetInstance<IProfileService>())
{
}

// CONSTRUCTOR
// -------------------------------------
UProfileViewModel::UProfileViewModel(FVTableHelper& Helper)
	: Super(Helper)
	, ProfileService(FJooballinServicesModule::GetTypeContainer().GetInstance<IProfileService>())
{
}

// DESTRUCTOR
// -------------------------------------
/*virtual*/ UProfileViewModel::~UProfileViewModel() = default;

// LoadProfile
// -------------------------------------
void UProfileViewModel::LoadProfile()
{
	UE_MVVM_SET_PROPERTY_VALUE(bIsProfileLoading, true);
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
