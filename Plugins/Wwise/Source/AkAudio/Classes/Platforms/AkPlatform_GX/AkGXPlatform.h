#pragma once

#ifdef AK_GX

#include "Platforms/AkPlatformBase.h"
#include "AkXboxOneAnvilInitializationSettings.h"

#define TCHAR_TO_AK(Text) (const WIDECHAR*)(Text)

using UAkInitializationSettings = UAkXboxOneAnvilInitializationSettings;

struct FAkGXPlatform : FAkPlatformBase
{
	static const UAkInitializationSettings* GetInitializationSettings()
	{
		return GetDefault<UAkXboxOneAnvilInitializationSettings>();
	}

	static const FString GetPlatformBasePath()
	{
		return FString("XboxOne");
	}
};

using FAkPlatform = FAkGXPlatform;

#endif
