// Fill out your copyright notice in the Description page of Project Settings.


#include "DA_InputConfig.h"

UInputAction* UDA_InputConfig::GetInputActionByTag(const FGameplayTag& InputTag,bool GiveWarning)
{
	for (FMyInputConfig& InputConfig : InputConfigs)
	{
		if (InputConfig.InputTag == InputTag)
		{
			return InputConfig.InputAction;
		}
	}
	if (GiveWarning)
	{
		GEngine->AddOnScreenDebugMessage(-1,10,FColor::Yellow,TEXT("No matching InputTag in Config"));
	}
	return nullptr;
}
