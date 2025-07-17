// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterEnemy.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"

ACharacterEnemy::ACharacterEnemy()
{
	AbilitySystemComponent=CreateDefaultSubobject<UMyAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet= CreateDefaultSubobject<UMyAttributeSet>("AttributeSet");
	
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
