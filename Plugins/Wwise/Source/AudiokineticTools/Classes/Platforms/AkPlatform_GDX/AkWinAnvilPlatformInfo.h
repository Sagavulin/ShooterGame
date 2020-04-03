#pragma once

#include "Platforms/AkPlatformInfo.h"
#include "AkWinAnvilPlatformInfo.generated.h"

UCLASS()
class UAkWinAnvilPlatformInfo : public UAkPlatformInfo
{
	GENERATED_BODY()

public:
	UAkWinAnvilPlatformInfo()
	{
		WwisePlatform = "Windows";

#ifdef AK_GDX_VS_VERSION
		Architecture = "GDX_" AK_WINDOWS_VS_VERSION;
#else
		Architecture = "GDX_vc150";
#endif

		LibraryFileNameFormat = "{0}.dll";
		DebugFileNameFormat = "{0}.pdb";
	}
};
