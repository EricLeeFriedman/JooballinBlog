// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class JooballinUE : ModuleRules
{
	public JooballinUE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		DefaultBuildSettings = BuildSettingsVersion.Latest;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core", 
			"CoreUObject", 
			"Engine",
			"InputCore"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"JooballinServices",
			"Json",
			"ModelViewViewModel"
		});
	}
}
