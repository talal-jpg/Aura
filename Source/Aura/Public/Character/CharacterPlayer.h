// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "CharacterPlayer.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API ACharacterPlayer : public ACharacterBase
{
	GENERATED_BODY()

	public:

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	void InitAbilityActorInfoAndSetASCASMemberVars();
	
};
