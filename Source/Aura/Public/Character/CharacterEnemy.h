// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "CharacterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ACharacterEnemy : public ACharacterBase
{
	GENERATED_BODY()
	public:
	ACharacterEnemy();

	virtual void BeginPlay() override;
	
};
