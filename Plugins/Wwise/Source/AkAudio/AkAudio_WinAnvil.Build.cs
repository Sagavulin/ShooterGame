// Copyright (c) 2006-2019 Audiokinetic Inc. / All Rights Reserved
using UnrealBuildTool;
using System;
using System.IO;
using System.Collections.Generic;

public class AkUEPlatform_WinAnvil : AkUEPlatform
{
	bool bIsDebugBuild = false;

	public AkUEPlatform_WinAnvil(ReadOnlyTargetRules in_TargetRules, string in_ThirdPartyFolder) : base(in_TargetRules, in_ThirdPartyFolder) {}

#if !UE_4_24_OR_LATER
	public override string SanitizeLibName(string in_libName)
	{
		return in_libName + ".lib";
	}
#endif

	public override string GetLibraryFullPath(string LibName, string LibPath)
	{
		return Path.Combine(LibPath, LibName + ".lib");
	}

	public override bool SupportsAkAutobahn { get { return false; } }

	public override bool SupportsCommunication { get { return true; } }

	public override bool SupportsOpus { get { return !bIsDebugBuild; } }

	public override List<string> GetPublicLibraryPaths()
	{
		string akPlatformLibDir = "GDX_" + GetVisualStudioVersion();
		var confDir = bIsDebugBuild && Target.Configuration == UnrealTargetConfiguration.Debug ? "Debug" : akConfigurationDir;
		return new List<string> { Path.Combine(ThirdPartyFolder, akPlatformLibDir, confDir, "lib") };
	}

	public override List<string> GetAdditionalWwiseLibs()
	{
		return new List<string>();
	}
	
	public override List<string> GetPublicSystemLibraries()
	{
		return new List<string> 
		{
			"dsound.lib",
			"dxguid.lib",
			"Msacm32.lib",
			"XInput.lib",
			"dinput8.lib"
		};
	}

	public override List<string> GetPublicDelayLoadDLLs()
	{
		return new List<string>();
	}

	public override List<string> GetPublicDefinitions()
	{
		return new List<string>
		{
            "AK_GDX",
			"AK_GDX_VS_VERSION=\"" + GetVisualStudioVersion() + "\""
		};
	}

	public override Tuple<string, string> GetAdditionalPropertyForReceipt(string ModuleDirectory)
	{
		return null;
	}

	public override List<string> GetPublicAdditionalFrameworks()
	{
		return new List<string>();
	}

	private string GetVisualStudioVersion()
	{
        // TODO: WinAnvilPlatform does not have a Compiler property
		return "vc150";
	}
}