// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerState.h"

#include "GAS/MyAbilitySystemComponent.h"
#include "GAS/MyAttributeSet.h"

AMyPlayerState::AMyPlayerState()
{
	AbilitySystemComponent=CreateDefaultSubobject<UMyAbilitySystemComponent>(FName("AbilitySystemComponent"));
	AttributeSet = CreateDefaultSubobject<UMyAttributeSet>(FName("AttributeSet"));
}

void AMyPlayerState::BeginPlay()
{
	Super::BeginPlay();
	
}
