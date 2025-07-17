// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerState.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"

AMyPlayerState::AMyPlayerState()
{
	AbilitySystemComponent=CreateDefaultSubobject<UMyAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet= CreateDefaultSubobject<UMyAttributeSet>("AttributeSet");
	SetReplicates(true);
}

UAbilitySystemComponent* AMyPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
