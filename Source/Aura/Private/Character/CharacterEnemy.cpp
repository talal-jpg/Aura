// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterEnemy.h"

#include "AbilitySystemComponent.h"

ACharacterEnemy::ACharacterEnemy()
{
	AbilitySystemComponent=CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet= CreateDefaultSubobject<UAttributeSet>("AttributeSet");
	
}

void ACharacterEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}

void ACharacterEnemy::Highlight()
{
	bIsHighlighted=true;
}

void ACharacterEnemy::UnHighlight()
{
	bIsHighlighted=false;
}
