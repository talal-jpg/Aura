// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GetHitResultUnderCursorData.h"
#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/MyPlayerController.h"

UGetHitResultUnderCursorData* UGetHitResultUnderCursorData::GetHitResultUnderCursor(UGameplayAbility* OwningAbility)
{
	// Ability
	UGetHitResultUnderCursorData* MyObj= NewAbilityTask<UGetHitResultUnderCursorData>(OwningAbility);
	return MyObj;
}

void UGetHitResultUnderCursorData::Activate()
{
	Super::Activate();
	bool bIsLocallyControlled=Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle=GetAbilitySpecHandle();
		FPredictionKey PredictionKey=GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpecHandle,PredictionKey).AddUObject(this,&ThisClass::OnTargetDataReplicatedCallback);
		bool bDelegateSent=AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(AbilitySpecHandle,PredictionKey);
		if (!bDelegateSent)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}


void UGetHitResultUnderCursorData::SendMouseCursorData()
{
	FHitResult HitResult;
	if (AMyPlayerController* PlayerController=Cast<AMyPlayerController>(AbilitySystemComponent->AbilityActorInfo->AvatarActor->GetInstigatorController()))
	{
		PlayerController->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
	}
	else
	{
		UKismetSystemLibrary::PrintString(this,"PC not found");
	}
	FScopedPredictionWindow PredictionWindow(AbilitySystemComponent.Get());
	FGameplayAbilitySpecHandle AbilitySpecHandle=GetAbilitySpecHandle();
	FGameplayAbilityTargetData_SingleTargetHit HitData;
	HitData.HitResult=HitResult;
	FGameplayAbilityTargetDataHandle AbilityTargetDataHandle;
	AbilityTargetDataHandle.Add(&HitData);
	AbilitySystemComponent->ServerSetReplicatedTargetData(AbilitySpecHandle,GetActivationPredictionKey(),AbilityTargetDataHandle,FGameplayTag(),AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		GetMouseTargetUnderCursorDataDelegate.Broadcast(AbilityTargetDataHandle);
	}
}

void UGetHitResultUnderCursorData::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		GetMouseTargetUnderCursorDataDelegate.Broadcast(DataHandle);
	}
}
