// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class CoreGameTarget : TargetRules
{
	public CoreGameTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		ExtraModuleNames.AddRange( new string[] { "CoreGame" } );
	}
	private static bool bHasWarnedAboutShared = false;

		static public bool ShouldEnableAllGameFeaturePlugins(TargetRules Target)
	{
		// Editor builds will build all game feature plugins, but it may or may not load them all.
		// This is so you can enable plugins in the editor without needing to compile code.
		if (Target.Type == TargetType.Editor)
		{
			return true;
		}

		// We always return true here because the example ConfigureGameFeaturePlugins()
		// doesn't have any additional logic to pick and choose which plugins to use.
		// If you add more complicated logic, you will want to return false here instead
		return true;
	}
}
