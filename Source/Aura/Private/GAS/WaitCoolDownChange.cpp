// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/WaitCoolDownChange.h"

#include <string>

#include "AbilitySystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"


UWaitCoolDownChange* UWaitCoolDownChange::WaitCoolDownChange(UAbilitySystemComponent* ASC,const FGameplayTag& InCoolDownTag)
{
	UWaitCoolDownChange* WaitCoolDownChange = NewObject<UWaitCoolDownChange>();
	// UKismetSystemLibrary::PrintString(WaitCoolDownChange,InCoolDownTag.ToString());
	WaitCoolDownChange->AbilitySystemComponent = ASC;
	WaitCoolDownChange->CoolDownTag = InCoolDownTag;
	if (!IsValid(ASC)|| !InCoolDownTag.IsValid())
	{
		WaitCoolDownChange->EndTask();
		return nullptr;
	}
	
	ASC->RegisterGameplayTagEvent(InCoolDownTag,EGameplayTagEventType::NewOrRemoved).AddUObject(WaitCoolDownChange,&UWaitCoolDownChange::CoolDownTagChanged);
	ASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCoolDownChange,&UWaitCoolDownChange::OnActiveEffectAdded);
	
	return WaitCoolDownChange;
}

void UWaitCoolDownChange::EndTask()
{
	if (!AbilitySystemComponent)return;
	AbilitySystemComponent->RegisterGameplayTagEvent(CoolDownTag,EGameplayTagEventType::NewOrRemoved).RemoveAll(this);

	SetReadyToDestroy();
	MarkAsGarbage();
}

void UWaitCoolDownChange::CoolDownTagChanged(const FGameplayTag InCoolDownTag, int32 NewCount)
{
	if (NewCount == 0)
	{
		CoolDownEnd.Broadcast(0);
	}
}

void UWaitCoolDownChange::OnActiveEffectAdded(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& GESpec,
	FActiveGameplayEffectHandle GEHandle)
{
	FGameplayTagContainer AssetTags;
	GESpec.GetAllAssetTags(AssetTags);
	
	FGameplayTagContainer GrantedTags;
	GESpec.GetAllGrantedTags(GrantedTags);
	

	if (AssetTags.HasTagExact(CoolDownTag)|| GrantedTags.HasTagExact(CoolDownTag))
	{
		// UKismetSystemLibrary::PrintString(this,"Active Effect Added"+ CoolDownTag.ToString());
		
		const FGameplayEffectQuery& GEQuery=FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CoolDownTag.GetSingleTagContainer());
		TArray<float> TimesRemaining=ASC->GetActiveEffectsTimeRemaining(GEQuery);
		CoolDownStart.Broadcast(TimesRemaining[0]);
	}
}


