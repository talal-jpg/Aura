// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Input/Data/DA_InputConfig.h"

UInputAction* UDA_InputConfig::GetInputActionByInputTag(FGameplayTag& InputTag)
{
	for (auto InputConfig : InputConfigs)
	{
		if (InputConfig.InputTag == InputTag)
		{
			return InputConfig.InputAction;
		}
	}
	return nullptr;
}
