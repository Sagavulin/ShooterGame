// Copyright (c) 2006-2018 Audiokinetic Inc. / All Rights Reserved

#include "Platforms/AkPlatform_GDX/AkWinAnvilInitializationSettings.h"
#include "AkAudioDevice.h"
#include "Runtime/HeadMountedDisplay/Public/IHeadMountedDisplayModule.h"

//////////////////////////////////////////////////////////////////////////
// FAkWinAnvilAdvancedInitializationSettings

void FAkWinAnvilAdvancedInitializationSettings::FillInitializationStructure(FAkInitializationStructure& InitializationStructure) const
{
	Super::FillInitializationStructure(InitializationStructure);

#ifdef AK_GDX
	if (UseHeadMountedDisplayAudioDevice && IHeadMountedDisplayModule::IsAvailable())
	{
		FString AudioOutputDevice = IHeadMountedDisplayModule::Get().GetAudioOutputDevice();
		if (!AudioOutputDevice.IsEmpty())
			InitializationStructure.InitSettings.settingsMainOutput.idDevice = AK::GetDeviceIDFromName((wchar_t*)*AudioOutputDevice);
	}

	InitializationStructure.PlatformInitSettings.eAudioAPI = static_cast<AkAudioAPI>(AudioAPI);
	InitializationStructure.PlatformInitSettings.bGlobalFocus = GlobalFocus;
#endif // AK_GDX
}


//////////////////////////////////////////////////////////////////////////
// UAkWinAnvilInitializationSettings

UAkWinAnvilInitializationSettings::UAkWinAnvilInitializationSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UAkWinAnvilInitializationSettings::FillInitializationStructure(FAkInitializationStructure& InitializationStructure) const
{

#ifdef AK_GDX_VS_VERSION
	constexpr auto PlatformArchitecture = "GDX_" AK_GDX_VS_VERSION;
#else
	constexpr auto PlatformArchitecture = "GDX_vc150";
#endif

	InitializationStructure.SetPluginDllPath(PlatformArchitecture);
	InitializationStructure.SetupLLMAllocFunctions();

	CommonSettings.FillInitializationStructure(InitializationStructure);
	CommunicationSettings.FillInitializationStructure(InitializationStructure);
	AdvancedSettings.FillInitializationStructure(InitializationStructure);

#ifdef AK_GDX
	InitializationStructure.PlatformInitSettings.uSampleRate = CommonSettings.SampleRate;
#endif
}
