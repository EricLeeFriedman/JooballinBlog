﻿// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "ProfileRepoImpl.h"

#include "MVVMS/Profile.h"

// CONSTRUCTOR
// -------------------------------------
FProfileRepoImpl::FProfileRepoImpl()
	: ProfileFilePath(FPaths::Combine(FPaths::GameSourceDir(), "JooballinUE", "Private", "MVVMS", "Profile.json"))
{
}

// GetProfileAsync
// -------------------------------------
/*virtual*/ TFuture<FProfile> FProfileRepoImpl::GetProfileAsync() const
{
	TSharedRef<TPromise<FProfile>> Promise = MakeShared<TPromise<FProfile>>();
	AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this, Promise]()
	{
		FProfile Profile;
		if (FPaths::FileExists(ProfileFilePath))
		{
			const TUniquePtr<FArchive> Ar(IFileManager::Get().CreateFileReader(*ProfileFilePath));
			const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Ar.Get());

			TSharedPtr<FJsonObject> ProfileJson;
			FJsonSerializer::Deserialize(Reader, ProfileJson);
			Profile.FromJson(ProfileJson);
		}
		Promise->SetValue(Profile);
	});
	return Promise->GetFuture();
}
