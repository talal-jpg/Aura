// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MyEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"

// Sets default values
AMyEffectActor::AMyEffectActor()
{
	

}

// Called when the game starts or when spawned
void AMyEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyEffectActor::OnOverlap(AActor* OtherActor)
{
	if (ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		IAbilitySystemInterface* ASI= Cast<IAbilitySystemInterface>(OtherActor);
		if (!ASI) return;
		 UAbilitySystemComponent* ASC= ASI->GetAbilitySystemComponent();
		// if (!ASC->GetAvatarActor()->HasAuthority())return;
		FGameplayEffectContextHandle EffectContextHandle=ASC->MakeEffectContext();
		EffectContextHandle.AddSourceObject(this);
		FGameplayEffectSpecHandle EffectSpecHandle=ASC->MakeOutgoingSpec(GameplayEffectClass,1,EffectContextHandle);
		FActiveGameplayEffectHandle ActiveEffectHandle=ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		
		ASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
		if (GameplayEffectClass.GetDefaultObject()->DurationPolicy==EGameplayEffectDurationType::Infinite && ASC)
		{
			ActiveEffectHandles.Add(ActiveEffectHandle,ASC);
		}
	}

}

void AMyEffectActor::OnEndOverlap(AActor* OtherActor)
{
	if (ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
	}
	if (RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		
		IAbilitySystemInterface* ASI= Cast<IAbilitySystemInterface>(OtherActor);
		if (!ASI) return;
		UAbilitySystemComponent* ASC= ASI->GetAbilitySystemComponent();

		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		for (auto Handle : ActiveEffectHandles)
		{
			if (ASC== Handle.Value)
			{
				ASC->RemoveActiveGameplayEffect(Handle.Key);
				HandlesToRemove.Add(Handle.Key);
			}
		}
		for (auto HandleToRemove : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(HandleToRemove);
		}
	}
}

void AMyEffectActor::ApplyEffect(AActor* OtherActor)
{
	if (IAbilitySystemInterface* AbilitySystemInterface= Cast<IAbilitySystemInterface>(OtherActor))
	{
	}
}

