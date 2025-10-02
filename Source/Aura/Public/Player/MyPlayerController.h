// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UNavigationPath;
class ICursorHitInterface;
class UDA_InputConfig;
struct FGameplayTag;
class UInputMappingContext;
class UInputAction;
class USplineComponent;

/**
 * 
 */
UCLASS()
class AURA_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	AMyPlayerController();
	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputMappingContext> Player_InputMappingContext;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UInputAction> IA_Move;


	UFUNCTION()
	void Move(const FInputActionValue& Val);


	void InputPressedFunc(FGameplayTag InputTag);

	void InputHeldFunc(FGameplayTag InputTag);

	void InputReleasedFunc(FGameplayTag InputTag);

	UPROPERTY(EditAnywhere)
	UDA_InputConfig* DA_InputConfig=nullptr;

	ICursorHitInterface* ThisActor=nullptr;
	ICursorHitInterface* LastActor=nullptr;
	
	UPROPERTY()
	USplineComponent* SplineComponent;

	UPROPERTY()
	FVector CachedLocation=FVector::ZeroVector;

	void CursorTrace();

	void AutoMove();

	bool bIsTargeting=false;

	FHitResult HitResult;

	float HeldTime=0.0f;
	float ShortPressThreshold=.5f;
	bool bIsAutoRunning=false;
	float DistanceThreshold=110.f;

	public:
	int foo=0;

	UPROPERTY(EditAnywhere)
	UNavigationPath* NavPath=nullptr;
	
};

