using UnrealBuildTool; 

public class CoreGame: ModuleRules 

{ 

	public CoreGame(ReadOnlyTargetRules Target) : base(Target) 

	{ 

		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				"CoreGame"
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
			}
		);
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreOnline",
				"CoreUObject",
				"Engine",
				"GameplayTags",
				"GameplayTasks",
				"AIModule",
				"InputCore",
				"OnlineSubsystemSteam",
				"UMG", 
				"HeadMountedDisplay" ,
				"OnlineSubsystem",
				"EnhancedInput"
			}
		);

		

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" }); 

	} 



}