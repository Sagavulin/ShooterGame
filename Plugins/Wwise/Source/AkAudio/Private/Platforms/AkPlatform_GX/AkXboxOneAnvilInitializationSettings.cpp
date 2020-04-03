// Copyright (c) 2006-2018 Audiokinetic Inc. / All Rights Reserved

#include "Platforms/AkPlatform_GX/AkXboxOneAnvilInitializationSettings.h"
#include "AkAudioDevice.h"

//////////////////////////////////////////////////////////////////////////
// FAkXboxOneAnvilAdvancedInitializationSettings

void FAkXboxOneAnvilAdvancedInitializationSettings::FillInitializationStructure(FAkInitializationStructure& InitializationStructure) const
{
	Super::FillInitializationStructure(InitializationStructure);

#ifdef AK_GX
	InitializationStructure.PlatformInitSettings.uMaxXMAVoices = MaximumNumberOfXMAVoices;
	InitializationStructure.PlatformInitSettings.bHwCodecLowLatencyMode = UseHardwareCodecLowLatencyMode;
#endif // AK_GX
}

//////////////////////////////////////////////////////////////////////////
// FAkXboxOneAnvilApuHeapInitializationSettings

void FAkXboxOneAnvilApuHeapInitializationSettings::FillInitializationStructure(FAkInitializationStructure& InitializationStructure) const
{
#ifdef AK_GX_NEED_APU_ALLOC
	// Perform this as early as possible to ensure that no other allocation calls are made before this!
	auto ApuCreateHeapResult = ApuCreateHeap(CachedSize, NonCachedSize);
	if (ApuCreateHeapResult == APU_E_HEAP_ALREADY_ALLOCATED)
	{
		UE_LOG(LogAkAudio, Warning, TEXT("APU heap has already been allocated."));
	}
	else if (ApuCreateHeapResult != S_OK)
	{
		UE_LOG(LogAkAudio, Warning, TEXT("APU heap could not be allocated."));
	}
#endif // AK_GX_NEED_APU_ALLOC
}


//////////////////////////////////////////////////////////////////////////
// UAkXboxOneAnvilInitializationSettings

UAkXboxOneAnvilInitializationSettings::UAkXboxOneAnvilInitializationSettings(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	CommonSettings.SamplesPerFrame = 512;

	CommunicationSettings.DiscoveryBroadcastPort = FAkCommunicationSettings::DefaultDiscoveryBroadcastPort;
	CommunicationSettings.CommandPort = FAkCommunicationSettings::DefaultDiscoveryBroadcastPort + 1;
	CommunicationSettings.NotificationPort = FAkCommunicationSettings::DefaultDiscoveryBroadcastPort + 2;
}

void UAkXboxOneAnvilInitializationSettings::FillInitializationStructure(FAkInitializationStructure& InitializationStructure) const
{
#ifdef AK_GX_VS_VERSION
	constexpr auto PlatformArchitecture = "GX_" AK_GX_VS_VERSION;
#else
	constexpr auto PlatformArchitecture = "GX_vc150";
#endif

	InitializationStructure.SetPluginDllPath(PlatformArchitecture);
	InitializationStructure.SetupLLMAllocFunctions();

	CommonSettings.FillInitializationStructure(InitializationStructure);
	ApuHeapSettings.FillInitializationStructure(InitializationStructure);
	CommunicationSettings.FillInitializationStructure(InitializationStructure);
	AdvancedSettings.FillInitializationStructure(InitializationStructure);
}
