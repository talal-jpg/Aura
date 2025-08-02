// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class USplineComponent;
struct FGameplayTag;
class UDA_InputConfig;
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

	UPROPERTY(EditAnywhere,Category = "Input")
	const UDA_InputConfig* DA_InputConfig;

	void Move(const FInputActionValue& Value);

	void AutoMove();

	void CursorTrace();

	void InputPressed( FGameplayTag InputTag);
	void InputHeld( FGameplayTag InputTag);
	void InputReleased( FGameplayTag InputTag);

	ICursorHitInterface* ThisActor=nullptr;
	ICursorHitInterface* LastActor=nullptr;

	bool bIsTargeting=false;

	float HeldTime=0;
	float ShortPressThreshold=.5f;
	FVector CachedDestination=FVector::ZeroVector;
	float AcceptableDistance=120.f;
	bool bIsAutoMoving=false;

	
	
	UPROPERTY()
	USplineComponent* Spline;
	
};
