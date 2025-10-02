// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Data/DA_AbilityInfo.h"

FAbilityInfo UDA_AbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag,bool bLogResult) const
{
	for (auto AbilityInfo:AbilitiesInfo)
	{
		if (AbilityInfo.AbilityTag == AbilityTag)
		{
			return AbilityInfo;
		}
		else if (bLogResult)
		{
			UE_LOG(LogTemp,Warning,TEXT("AbilityInfoNotFoundForTag%s"),*AbilityTag.ToString());
		}
	}
	return FAbilityInfo();
}
