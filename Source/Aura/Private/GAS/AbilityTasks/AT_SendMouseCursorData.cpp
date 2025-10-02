// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AbilityTasks/AT_SendMouseCursorData.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/GameSession.h"

UAT_SendMouseCursorData* UAT_SendMouseCursorData::GetSendMouseCursorDataTaskInstance(UGameplayAbility* OwningAbility)
{
	return NewAbilityTask<UAT_SendMouseCursorData>(OwningAbility);
}

void UAT_SendMouseCursorData::Activate()
{
	Super::Activate();
	bool bIsLocalController= GetAvatarActor()->GetInstigatorController()->IsLocalController();
	if (bIsLocalController)
	{
		FScopedPredictionWindow PredictionWindow= FScopedPredictionWindow(AbilitySystemComponent.Get());
		APlayerController* PC=Cast<APlayerController>(GetAvatarActor()->GetInstigatorController());
		FHitResult HitResult;
		// if (!PC)return;
		PC->GetHitResultUnderCursor(ECC_Visibility,false, HitResult);
		FGameplayAbilityTargetData_SingleTargetHit* TargetData_SingleHit=new FGameplayAbilityTargetData_SingleTargetHit();
		TargetData_SingleHit->HitResult=HitResult;
		FGameplayAbilityTargetDataHandle TargetDataHandle;
		TargetDataHandle.Add(TargetData_SingleHit);
		AbilitySystemComponent.Get()->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey(),TargetDataHandle,FGameplayTag(),AbilitySystemComponent->ScopedPredictionKey);
		
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnReplicatedDataSetSendMouseCursorDataDelegate.Broadcast(TargetDataHandle);
		}
	}
	else if (!bIsLocalController)
	{
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),GetActivationPredictionKey()).AddUObject(this,&ThisClass::OnTargetDataSetBroadcastMouseCursorDataDelegateCallback);
		bool bIsCalled=AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey());
		if (!bIsCalled)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UAT_SendMouseCursorData::OnTargetDataSetBroadcastMouseCursorDataDelegateCallback(
	const FGameplayAbilityTargetDataHandle& TargetDataHandle, FGameplayTag GameplayTag)
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnReplicatedDataSetSendMouseCursorDataDelegate.Broadcast(TargetDataHandle);
	}
}
