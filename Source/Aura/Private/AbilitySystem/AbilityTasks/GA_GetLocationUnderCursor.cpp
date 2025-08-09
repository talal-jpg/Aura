// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/GA_GetLocationUnderCursor.h"

#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"

UGA_GetLocationUnderCursor* UGA_GetLocationUnderCursor::TaskInstance(UGameplayAbility* OwningAbility)
{
	
	return NewAbilityTask<UGA_GetLocationUnderCursor>(OwningAbility);
}

void UGA_GetLocationUnderCursor::Activate()
{
	Super::Activate();
	bool bIsLocallyControlled=Ability->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		FScopedPredictionWindow PredictionWindow=FScopedPredictionWindow(AbilitySystemComponent.Get());
		APlayerController* PC=UGameplayStatics::GetPlayerController(GetWorld(),0);
		UKismetSystemLibrary::PrintString(this,PC->GetName());
		FHitResult HitResult;
		PC->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
		FGameplayAbilityTargetData_SingleTargetHit* TargetData_SingleTargetHit=new FGameplayAbilityTargetData_SingleTargetHit;
		TargetData_SingleTargetHit->HitResult = HitResult;
		FGameplayAbilityTargetDataHandle TargetData_Handle;
		TargetData_Handle.Add(TargetData_SingleTargetHit);
		AbilitySystemComponent.Get()->CallServerSetReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey(),TargetData_Handle,FGameplayTag(),AbilitySystemComponent->ScopedPredictionKey);
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			OnClickBroadcastTargetDataDelegate.Broadcast(TargetData_Handle);
			UKismetSystemLibrary::PrintString(this,"BroadcastFromClient");
		}
	}
	else
	{
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(GetAbilitySpecHandle(),GetActivationPredictionKey()).AddUObject(this,&ThisClass::OnTargetDataSetDelegateCallback);
		bool bIsCalled=AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(GetAbilitySpecHandle(),GetActivationPredictionKey());
		if (!bIsCalled)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UGA_GetLocationUnderCursor::OnTargetDataSetDelegateCallback(
	const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, FGameplayTag GameplayTag)
{
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(),GetActivationPredictionKey());
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnClickBroadcastTargetDataDelegate.Broadcast(AbilityTargetDataHandle);
	}
}
