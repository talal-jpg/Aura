// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class UDA_DefaultEnemyAttributes;
/**
 * 
 */
UCLASS()
class AURA_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()


	public:
	UPROPERTY(EditAnywhere)
	UDA_DefaultEnemyAttributes* DefaultEnemyAttributesInfo;
	
};
