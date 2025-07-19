// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MyEffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Runtime/Engine/Internal/Kismet/BlueprintTypeConversions.h"

// Sets default values
AMyEffectActor::AMyEffectActor()
{
	MyRootComponent=CreateDefaultSubobject<USceneComponent>("RootComponent");
	SetRootComponent(MyRootComponent);
}

// Called when the game starts or when spawned
void AMyEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMyEffectActor::OnOverlap(AActor* OtherActor)
{
	if ( IAbilitySystemInterface* OtherActorAsASI = Cast<IAbilitySystemInterface>(OtherActor))
	{
		UAbilitySystemComponent* OtherActorsAsc=OtherActorAsASI->GetAbilitySystemComponent();
		if (EffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnOverlap)
		{
			FGameplayEffectContextHandle ContextHandle;
			FGameplayEffectSpecHandle GESpecHandle = OtherActorsAsc->MakeOutgoingSpec(GameplayEffectClass, 1, ContextHandle);
			FGameplayEffectSpec* GESpec = GESpecHandle.Data.Get();
			
			FActiveGameplayEffectHandle ActiveGameplayEffectHandle=OtherActorsAsc->ApplyGameplayEffectSpecToSelf(*GESpec);
			if (GESpec->Def->DurationPolicy==EGameplayEffectDurationType::Infinite)
			{
				ActiveGameplayEffectHandles.Add(ActiveGameplayEffectHandle,OtherActorsAsc);
			}
		}
	}
}

void AMyEffectActor::OnEndOverlap(AActor* OtherActor)
{
	if ( IAbilitySystemInterface* OtherActorAsASI = Cast<IAbilitySystemInterface>(OtherActor))
	{
		UAbilitySystemComponent* OtherActorsAsc=OtherActorAsASI->GetAbilitySystemComponent();
		if (EffectRemovalPolicy== EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			TArray<FActiveGameplayEffectHandle> HandlesToRemove;
			for (auto ActiveGameplayEffectHandle : ActiveGameplayEffectHandles)
			{
				if (ActiveGameplayEffectHandle.Value==OtherActorsAsc)
				{
					OtherActorsAsc->RemoveActiveGameplayEffect(ActiveGameplayEffectHandle.Key);
					HandlesToRemove.Add(ActiveGameplayEffectHandle.Key);
				}
			}

			for (auto Handle : HandlesToRemove)
			{
				ActiveGameplayEffectHandles.Remove(Handle);
			}
		}
		if (EffectApplicationPolicy==EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			FGameplayEffectContextHandle ContextHandle;
			FGameplayEffectSpecHandle GESpecHandle = OtherActorsAsc->MakeOutgoingSpec(GameplayEffectClass, 1, ContextHandle);
			FGameplayEffectSpec* GESpec = GESpecHandle.Data.Get();
			
			FActiveGameplayEffectHandle ActiveGameplayEffectHandle=OtherActorsAsc->ApplyGameplayEffectSpecToSelf(*GESpec);
		}
	}
}

