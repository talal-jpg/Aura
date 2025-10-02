// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Data/DA_InputConfig.h"
#include "MyEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMyEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

	public:
	template <class UserObject, typename FuncTypeInputPressed, typename FuncTypeInputHeld, typename FuncTypeInputReleased>
	void BindInputAbilityAction(UserObject Object,UDA_InputConfig* DA_InputConfig,FuncTypeInputPressed FuncInputPressed,FuncTypeInputHeld FuncInputHeld,FuncTypeInputReleased FuncInputReleased);
};

template <class UserObject, typename FuncTypeInputPressed, typename FuncTypeInputHeld, typename FuncTypeInputReleased>
void UMyEnhancedInputComponent::BindInputAbilityAction(UserObject Object,UDA_InputConfig* DA_InputConfig,FuncTypeInputPressed FuncInputPressed,FuncTypeInputHeld FuncInputHeld,FuncTypeInputReleased FuncInputReleased)
{
	for (auto InputConfig:DA_InputConfig->InputConfigs)
	{
		if (FuncInputPressed)
		{
			BindAction(InputConfig.InputAction,ETriggerEvent::Started,Object,FuncInputPressed,InputConfig.InputTag);
		}
		if (FuncInputHeld)
		{
			BindAction(InputConfig.InputAction,ETriggerEvent::Triggered,Object,FuncInputHeld,InputConfig.InputTag);
		}
		if (FuncInputReleased)
		{
			BindAction(InputConfig.InputAction,ETriggerEvent::Completed,Object,FuncInputReleased,InputConfig.InputTag);
		}
	}
}
