// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "Interface/CursorHitInterface.h"
#include "CharacterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ACharacterEnemy : public ACharacterBase , public ICursorHitInterface
{
	GENERATED_BODY()
	public:
	ACharacterEnemy();

	virtual void BeginPlay() override;

	virtual void Highlight() override;
	virtual void UnHighlight() override;

	UPROPERTY(BlueprintReadWrite)
	bool bIsHighlighted;
};
