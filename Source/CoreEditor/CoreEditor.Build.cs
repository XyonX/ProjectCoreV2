using UnrealBuildTool; 

public class CoreEditor: ModuleRules 

{ 

public CoreEditor(ReadOnlyTargetRules Target) : base(Target) 

{ 

PrivateDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine"}); 

} 

}