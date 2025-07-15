// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"

#include <functional>

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interface/CursorHitInterface.h"
#include "Player/MyEnhancedInputComponent.h"

AMyPlayerController::AMyPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor= EMouseCursor::Default;
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(PlayerInputMappingContext,1);

	if (InputComponent)
	{
		UMyEnhancedInputComponent* MyEnhancedInputComponent= Cast<UMyEnhancedInputComponent>(InputComponent);
		MyEnhancedInputComponent->BindAction(IA_Move,ETriggerEvent::Triggered,this,&AMyPlayerController::Move);
		MyEnhancedInputComponent->BindInputAbilityAction(this,DA_InputConfig,&ThisClass::InputPressed,&ThisClass::InputHeld,&ThisClass::InputReleased);
	}
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CursorTrace();
}

void AMyPlayerController::Move(const FInputActionValue& Value)
{
	FVector2D Val=Value.Get<FVector2D>();
	FRotator Rot=FRotator(0,GetControlRotation().Yaw,0);
	FVector Forward= FRotationMatrix(Rot).GetUnitAxis(EAxis::X);
	FVector Side= FRotationMatrix(Rot).GetUnitAxis(EAxis::Y);
	GetPawn()->AddMovementInput(Forward,Val.X);
	GetPawn()->AddMovementInput(Side,Val.Y);
}

void AMyPlayerController::CursorTrace()
{
	FHitResult CursorHitResult;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHitResult);
	LastActor=ThisActor;
	if (CursorHitResult.bBlockingHit)
	{
		ThisActor= Cast<ICursorHitInterface>(CursorHitResult.GetActor());
	}
	if (LastActor!=ThisActor)
	{
		if (LastActor)
		{
			LastActor->UnHighlight();
		}
		if (ThisActor)
		{
			ThisActor->Highlight();
		}
	}
}

void AMyPlayerController::InputPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(-1,10,FColor::Red,InputTag.ToString());
}

void AMyPlayerController::InputHeld(FGameplayTag InputTag)
{
	
}

void AMyPlayerController::InputReleased(FGameplayTag InputTag)
{
}
