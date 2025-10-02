// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/My_CharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraLensEffectInterface.h"
#include "GAS/GameplayAbility/MyGameplayAbility.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/MyPlayerController.h"
#include "Player/MyPlayerState.h"
#include "UI/MyHUD.h"

void AMy_CharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	APlayerController* MyPlayerController=Cast<APlayerController>(GetController());
	if (!MyPlayerController)
	{
		UKismetSystemLibrary::PrintString(this,"NoPlayerController");
		return;
	}
	
	AMyHUD* MyHUD=Cast<AMyHUD>(MyPlayerController->GetHUD());
	if (MyHUD)
	{
		MyHUD->InitOverlay();
	}
}

void AMy_CharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfo();
	if (APlayerController* PC=GetController<AMyPlayerController>())
	{
		if (AMyHUD* MyHUD=Cast<AMyHUD>(PC->GetHUD()))
		{
			MyHUD->InitOverlay();
		}
	}
}

void AMy_CharacterPlayer::InitAbilityActorInfo()
{
	
	AMyPlayerState* MyPlayerState=GetPlayerState<AMyPlayerState>();
	AbilitySystemComponent = MyPlayerState->AbilitySystemComponent;
	AttributeSet = MyPlayerState->AttributeSet;
	AbilitySystemComponent->InitAbilityActorInfo(MyPlayerState,this);
	InitializeDefaultAttributes();
	GiveStartupAbilities();
}

UAbilitySystemComponent* AMy_CharacterPlayer::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AMy_CharacterPlayer::InitializeDefaultAttributes()
{
	ApplyEffect(DefaultPrimaryAttributes);
	ApplyEffect(DefaultSecondaryAttributes);
	ApplyEffect(DefaultVitalAttributes);
}

void AMy_CharacterPlayer::ApplyEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	FGameplayEffectContextHandle EffectContextHandle=AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle=AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass,1,EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

