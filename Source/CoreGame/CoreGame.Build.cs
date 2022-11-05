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
			}
		);

		

		PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine","OnlineSubsystemSteam","OnlineSubsystem","GameplayTags","InputCore", "EnhancedInput" }); 

	} 



}