// Fill out your copyright notice in the Description page of Project Settings.


using UnrealBuildTool;

public class ProjectL_Main : ModuleRules
{
    public ProjectL_Main(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "GameplayTasks",
            "Slate",
            "SlateCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
	// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	
