// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"

#include <functional>

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interface/CursorHitInterface.h"

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
		UEnhancedInputComponent* EnhancedInputComponent= Cast<UEnhancedInputComponent>(InputComponent);
		EnhancedInputComponent->BindAction(IA_Move,ETriggerEvent::Triggered,this,&AMyPlayerController::Move);
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
	if (!CursorHitResult.bBlockingHit)return;
	ICursorHitInterface* HitActor=Cast<ICursorHitInterface>(CursorHitResult.GetActor());
	if (!HitActor)return;
	ThisActor=HitActor;
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
