// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DA_InputConfig.h"
#include "EnhancedInputComponent.h"
#include "MyEnhancedInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UMyEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

	public:
	template <class UserClass,typename PressedFuncType,typename HeldFuncType,typename ReleasedFuncType>
	void BindInputAbilityAction(UserClass Object,const UDA_InputConfig* DA_InputConfig, PressedFuncType PressedFunc,HeldFuncType HeldFunc, ReleasedFuncType ReleasedFunc);

};

template <class UserClass, typename PressedFuncType, typename HeldFuncType, typename ReleasedFuncType>
void UMyEnhancedInputComponent::BindInputAbilityAction(UserClass Object,const UDA_InputConfig* DA_InputConfig,PressedFuncType PressedFunc, HeldFuncType HeldFunc, ReleasedFuncType ReleasedFunc)
{
		for (FMyInputConfig InputConfig: DA_InputConfig->InputConfigs)
		{
			if (InputConfig.InputTag.IsValid()&& InputConfig.InputAction)
			{
				if (PressedFunc)
				{
					BindAction(InputConfig.InputAction,ETriggerEvent::Started,Object,PressedFunc,InputConfig.InputTag);
				}
				if (HeldFunc)
				{
					BindAction(InputConfig.InputAction,ETriggerEvent::Triggered,Object,HeldFunc,InputConfig.InputTag);
				}
				if (ReleasedFunc)
				{
					BindAction(InputConfig.InputAction,ETriggerEvent::Completed,Object,HeldFunc,InputConfig.InputTag);
				}
				
			}
		}
}
