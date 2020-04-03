// Copyright (c) 2006-2019 Audiokinetic Inc. / All Rights Reserved
using UnrealBuildTool;
using System;
using System.IO;
using System.Collections.Generic;

public class AkUEPlatform_XboxOneAnvil : AkUEPlatform
{
	public AkUEPlatform_XboxOneAnvil(ReadOnlyTargetRules in_TargetRules, string in_ThirdPartyFolder) : base(in_TargetRules, in_ThirdPartyFolder) {}

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

	public override List<string> GetPublicLibraryPaths()
	{
		var akPlatformLibDir = "GX_" + GetVisualStudioVersion();

		return new List<string>
		{
			Path.Combine(ThirdPartyFolder, akPlatformLibDir, akConfigurationDir, "lib")
		};
	}

	public override List<string> GetAdditionalWwiseLibs()
	{
		return new List<string>();
	}
	
	public override List<string> GetPublicSystemLibraries()
	{
		return new List<string>
		{
			"AcpHal.lib",
			"MMDevApi.lib"
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
			"_GAMING_XBOX",
			"AK_GAMINGXBOX",
			"AK_GX",
			"AK_NEED_XBOX_MINAPI=0",
			"AK_XBOXONE_INIT_COMMS_MANIFEST=0",
			"AK_GX_VS_VERSION=\"" + GetVisualStudioVersion() + "\"",
			"AK_GX_NEED_APU_ALLOC"
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
        // TODO: XboxOneAnvilPlatform does not have a Compiler property
		return "vc150";
	}
}
