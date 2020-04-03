#pragma once

#include "Platforms/AkPlatformInfo.h"
#include "AkXboxOneAnvilPlatformInfo.generated.h"

UCLASS()
class UAkXboxOneAnvilPlatformInfo : public UAkPlatformInfo
{
	GENERATED_BODY()

public:
	UAkXboxOneAnvilPlatformInfo()
	{
		WwisePlatform = "XboxOne";

#ifdef AK_GX_VS_VERSION
		Architecture = "GX_" AK_GX_VS_VERSION;
#else
		Architecture = "GX_vc150";
#endif

		LibraryFileNameFormat = "{0}.dll";
		DebugFileNameFormat = "{0}.pdb";
	}
};
