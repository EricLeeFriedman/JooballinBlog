﻿using UnrealBuildTool;

public class JooballinServices : ModuleRules
{
    public JooballinServices(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Json",
                "Slate",
                "SlateCore"
            }
        );
    }
}