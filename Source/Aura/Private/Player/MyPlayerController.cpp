// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"

#include <functional>

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystem/MyGameplayTags.h"
#include "Components/SplineComponent.h"
#include "Interface/CursorHitInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/MyEnhancedInputComponent.h"
#include "Player/MyPlayerState.h"

AMyPlayerController::AMyPlayerController()
{
	Spline=CreateDefaultSubobject<USplineComponent>("Spline");
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
	AutoMove();
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

void AMyPlayerController::AutoMove()
{
	if (!bIsAutoMoving) return;
	FVector ClosestLocation=Spline->FindLocationClosestToWorldLocation(GetPawn()->GetActorLocation(),ESplineCoordinateSpace::World);
	FVector DirectionVector= Spline->FindDirectionClosestToWorldLocation(ClosestLocation,ESplineCoordinateSpace::World);

	int32 PntNum=Spline->GetNumberOfSplinePoints();
	FVector LastPointLoc=Spline->GetLocationAtSplinePoint(PntNum,ESplineCoordinateSpace::World);
	float Distance= (LastPointLoc-GetPawn()->GetActorLocation()).Length();
	
	if (Distance>AcceptableDistance)
	{
		GetPawn()->AddMovementInput(DirectionVector,1);
	}
	else
	{
		bIsAutoMoving=false;
	}
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
	
//	UKismetSystemLibrary::PrintString(this,InputTag.ToString());
//	UGameplayTagsManager::Get().RequestGameplayTag(FName("Input.LMB"));
//	UKismetSystemLibrary::PrintString(this,InputTag.ToString());
	
UAbilitySystemComponent* ASC=GetPlayerState<AMyPlayerState>()->AbilitySystemComponent;
	for (auto Ability:ASC->GetActivatableAbilities())
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle;
		ASC->TryActivateAbility(Ability.Handle);
		Ability.InputPressed=true;
	}
}

void AMyPlayerController::InputHeld(FGameplayTag InputTag)
{
	if (InputTag== UGameplayTagsManager::Get().RequestGameplayTag(FName("Input.LMB")))
	{
		HeldTime+=GetWorld()->GetDeltaSeconds();
		//UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("HeldTime: %f"),HeldTime));
		
		FHitResult HitResult;
		GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
		CachedDestination=HitResult.ImpactPoint;
		FVector Dir= (CachedDestination-GetPawn()->GetActorLocation()).GetSafeNormal();
		GetPawn()->AddMovementInput(Dir,1);
	}
}

void AMyPlayerController::InputReleased(FGameplayTag InputTag)
{
	if (HeldTime<ShortPressThreshold)
	{
		if (APawn* ControlledPawn=GetPawn())
		{
			FVector Start=ControlledPawn->GetActorLocation();
			
			UNavigationPath* NavPath= UNavigationSystemV1::FindPathToLocationSynchronously(GetPawn(),Start,CachedDestination);
			Spline->ClearSplinePoints();
			for (auto Point:NavPath->PathPoints)
			{
				Spline->AddSplinePoint(Point,ESplineCoordinateSpace::World);
			}
		}
		bIsAutoMoving=true;
	}
	HeldTime=0;
}
