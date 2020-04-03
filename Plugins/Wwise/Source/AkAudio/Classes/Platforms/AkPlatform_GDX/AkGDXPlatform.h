#pragma once

#ifdef AK_GDX

#include "Platforms/AkPlatformBase.h"
#include "AkWinAnvilInitializationSettings.h"

#define TCHAR_TO_AK(Text) (const WIDECHAR*)(Text)

using UAkInitializationSettings = UAkWinAnvilInitializationSettings;

struct FAkGDXPlatform : FAkPlatformBase
{
	static const UAkInitializationSettings* GetInitializationSettings()
	{
		return GetDefault<UAkWinAnvilInitializationSettings>();
	}

	static const FString GetPlatformBasePath()
	{
		return FString("Windows");
	}
};

using FAkPlatform = FAkGDXPlatform;

#endif
