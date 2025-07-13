// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerState.h"
#include "AbilitySystemComponent.h"

AMyPlayerState::AMyPlayerState()
{
	AbilitySystemComponent=CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet= CreateDefaultSubobject<UAttributeSet>("AttributeSet");
	SetReplicates(true);
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
