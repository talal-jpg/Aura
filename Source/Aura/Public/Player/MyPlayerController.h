// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class ICursorHitInterface;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class AURA_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	AMyPlayerController();
	
	virtual void SetupInputComponent() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerInputMappingContext;

	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> IA_Move;

	void Move(const FInputActionValue& Value);

	void CursorTrace();

	ICursorHitInterface* ThisActor=nullptr;
	ICursorHitInterface* LastActor=nullptr;
};
