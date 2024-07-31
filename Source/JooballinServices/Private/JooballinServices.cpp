// License Copyright (c) 2024 Eric Friedman

// Includes
// -------------------------------------
#include "JooballinServices.h"

#include "MVVMS/ProfileRepoImpl.h"
#include "MVVMS/ProfileService.h"
#include "MVVMS/ProfileServiceImpl.h"

// Static Initialization
// -------------------------------------
/*static*/ TTypeContainer<> FJooballinServicesModule::TypeContainer;

// GetTypeContainer
// -------------------------------------
/*static*/ TTypeContainer<>& FJooballinServicesModule::GetTypeContainer()
{
	return TypeContainer;
}

// StartupModule
// -------------------------------------
/*virtual*/ void FJooballinServicesModule::StartupModule()
{
	TypeContainer.RegisterClass<IProfileRepo, FProfileRepoImpl>();

	const TSharedRef<IProfileService> ProfileService = MakeShared<FProfileServiceImpl>(TypeContainer.GetInstance<IProfileRepo>());
	TypeContainer.RegisterInstance<IProfileService>(ProfileService);
}

// ShutdownModule
// -------------------------------------
/*virtual*/ void FJooballinServicesModule::ShutdownModule()
{
    TypeContainer.Unregister<IProfileRepo>();
	TypeContainer.Unregister<IProfileService>();
}

IMPLEMENT_MODULE(FJooballinServicesModule, JooballinServices)