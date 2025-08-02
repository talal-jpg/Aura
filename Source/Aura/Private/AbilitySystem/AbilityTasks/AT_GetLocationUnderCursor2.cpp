// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AT_GetLocationUnderCursor2.h"

#include "AbilitySystemComponent.h"

UAT_GetLocationUnderCursor2* UAT_GetLocationUnderCursor2::TaskInstance(UGameplayAbility* OwningAbility)
{
	return NewAbilityTask<UAT_GetLocationUnderCursor2>(OwningAbility);
}

void UAT_GetLocationUnderCursor2::Activate()
{
	Super::Activate();
	bool bIsLocallyControlled=Ability->GetActorInfo().IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		if (APlayerController* PlayerCont=Cast<APlayerController>(AbilitySystemComponent.Get()->GetAvatarActor()->GetInstigatorController()))
		{
			FScopedPredictionWindow ScopedPredictionWindow=FScopedPredictionWindow(AbilitySystemComponent.Get());
			FHitResult HitResult;
			PlayerCont->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
			FGameplayAbilityTargetData_SingleTargetHit* TargetData=new FGameplayAbilityTargetData_SingleTargetHit();
			TargetData->HitResult=HitResult;
			FGameplayAbilityTargetDataHandle TargetDataHandle;
			TargetDataHandle.Add(TargetData);
			AbilitySystemComponent.Get()->CallServerSetReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey(),TargetDataHandle,FGameplayTag(),AbilitySystemComponent->ScopedPredictionKey);
			
			if (ShouldBroadcastAbilityTaskDelegates())
			{
				OnTargetDataSetBroadcastLocation.Broadcast(TargetDataHandle);
			}
		}
	}
	else
	{
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),GetActivationPredictionKey()).AddUObject(this,&ThisClass::TargetDataSetDelegateCallback);
		bool bIsCalled=AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey());
		if (!bIsCalled)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UAT_GetLocationUnderCursor2::TargetDataSetDelegateCallback(
	const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, FGameplayTag GameplayTag)
{
	AbilitySystemComponent.Get()->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTargetDataSetBroadcastLocation.Broadcast(AbilityTargetDataHandle);
	}
}
