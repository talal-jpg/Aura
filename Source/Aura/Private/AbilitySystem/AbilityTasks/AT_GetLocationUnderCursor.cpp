// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AT_GetLocationUnderCursor.h"

#include "AbilitySystemComponent.h"
#include "Player/MyPlayerController.h"

UAT_GetLocationUnderCursor* UAT_GetLocationUnderCursor::AT_GetLocationUnderCursor(UGameplayAbility* OwningAbility)
{
	return NewAbilityTask<UAT_GetLocationUnderCursor>(OwningAbility, TEXT("AT_GetLocationUnderCursor"));
}

void UAT_GetLocationUnderCursor::Activate()
{
	Super::Activate();
	bool bIsLocallyControlled = AbilitySystemComponent->AbilityActorInfo->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle=GetAbilitySpecHandle();
		FPredictionKey PredictionKey= GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpecHandle,PredictionKey).AddUObject(this,&ThisClass::TargetDataDelegateCallBack);
		bool bIsBroadcasted=AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(AbilitySpecHandle,PredictionKey);
		if (!bIsBroadcasted)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UAT_GetLocationUnderCursor::SendMouseCursorData()
{
	if (AMyPlayerController* MyPlayerController=Cast<AMyPlayerController>(Ability->GetActorInfo().AvatarActor->GetInstigatorController()))
	{
		FScopedPredictionWindow PredictionWindow(AbilitySystemComponent.Get());
		FHitResult HitResult;
		MyPlayerController->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
		FGameplayAbilityTargetData_SingleTargetHit* TargetData_SingleTargetHit=new FGameplayAbilityTargetData_SingleTargetHit();
		TargetData_SingleTargetHit->HitResult = HitResult;
		FGameplayAbilityTargetDataHandle TargetDataHandle;
		TargetDataHandle.Add(TargetData_SingleTargetHit);
		AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey(),TargetDataHandle,FGameplayTag(),AbilitySystemComponent->ScopedPredictionKey);
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			GetLocationUnderCursorDelegate.Broadcast(TargetDataHandle);
		}
	}
}

void UAT_GetLocationUnderCursor::TargetDataDelegateCallBack(const FGameplayAbilityTargetDataHandle& TargetDataHandle,
	FGameplayTag GameplayTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		GetLocationUnderCursorDelegate.Broadcast(TargetDataHandle);
	}
}
