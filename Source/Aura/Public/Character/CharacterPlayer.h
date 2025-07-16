// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "CharacterPlayer.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS()
class AURA_API ACharacterPlayer : public ACharacterBase
{
	GENERATED_BODY()

	public:
	ACharacterPlayer();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmComponent> CameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UCameraComponent> Camera;

	virtual void PossessedBy(AController* NewController) override;

	virtual void OnRep_PlayerState() override;

	void InitAbilityActorInfoAndSetASCASMemberVars();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;

	void GiveStartUpAbilities();
};
