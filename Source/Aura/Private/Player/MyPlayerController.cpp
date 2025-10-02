// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MyPlayerController.h"

#include <string>

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "AbilitySystem/MyGameplayTags.h"
#include "Character/My_CharacterPlayer.h"
#include "Components/SplineComponent.h"
#include "GameFramework/Character.h"
#include "GAS/MyAttributeSet.h"
#include "Interface/CursorHitInterface.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/MyPlayerState.h"
#include "Player/Input/MyEnhancedInputComponent.h"

AMyPlayerController::AMyPlayerController()
{

	SplineComponent=CreateDefaultSubobject<USplineComponent>("SplineComponent");
	bShowMouseCursor=true;
	DefaultMouseCursor=EMouseCursor::Default;
}

void AMyPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CursorTrace();
	AutoMove();

	UKismetSystemLibrary::DrawDebugCircle(this,CachedLocation,100);
	bIsTargeting=ThisActor ? true: false ;

	//
	// if (bIsTargeting)
	// {
	// UKismetSystemLibrary::PrintString(this,"Targeting");
	// }
	
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(Player_InputMappingContext,0);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	// FInputModeGameAndUI GameModeAndUI;
	// GameModeAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// APlayerController::SetInputMode(GameModeAndUI);
	
	UMyEnhancedInputComponent* MyEnhancedInputComponent=Cast<UMyEnhancedInputComponent>(InputComponent);
	if (!MyEnhancedInputComponent)return;
	MyEnhancedInputComponent->BindAction(IA_Move,ETriggerEvent::Triggered,this,&ThisClass::Move);
	MyEnhancedInputComponent->BindInputAbilityAction(this,DA_InputConfig,&ThisClass::InputPressedFunc,&ThisClass::InputHeldFunc,&ThisClass::InputReleasedFunc);
}

void AMyPlayerController::Move(const FInputActionValue& Val)
{
	FVector2D Value=Val.Get<FVector2D>();
	FRotator Rot=GetControlRotation();
	Rot.Pitch=0;
	FRotationMatrix RotMat=FRotationMatrix(Rot);
	FVector ForwardDir= RotMat.GetUnitAxis(EAxis::X);
	FVector SideDir= RotMat.GetUnitAxis(EAxis::Y);
	GetCharacter()->AddMovementInput(ForwardDir,Value.X);
	GetCharacter()->AddMovementInput(SideDir,Value.Y);
}

void AMyPlayerController::InputPressedFunc(FGameplayTag InputTag)
{

	AMy_CharacterPlayer* MyChar=Cast<AMy_CharacterPlayer>(GetPawn());

	if (bIsTargeting)
	{
		TArray<FGameplayAbilitySpec> Abilities = MyChar->AbilitySystemComponent.Get()->GetActivatableAbilities();
		for(auto Ability: Abilities)
		{
			if (Ability.DynamicAbilityTags.HasTagExact(InputTag))
			{
				MyChar->AbilitySystemComponent->TryActivateAbility(Ability.Handle);
			}
			else
			{
				FGameplayTagContainer Tags=Ability.GetDynamicSpecSourceTags();
				for (auto Tag : Tags)
				{
					UKismetSystemLibrary::PrintString(this,Tag.ToString());
				}
			}
		}
	}
	
	FString String=InputTag.ToString();
	// UKismetSystemLibrary::PrintString(this,String+FString("Pressed"));
}

void AMyPlayerController::InputHeldFunc(FGameplayTag InputTag)
{
	// FString String=InputTag.ToString();
	
	if (!bIsTargeting)
	{
		HeldTime=0;
		HeldTime+=GetWorld()->GetTimeSeconds();
		CachedLocation=HitResult.ImpactPoint;
		NavPath=UNavigationSystemV1::FindPathToLocationSynchronously(this,GetPawn()->GetActorLocation(),CachedLocation);
		if (NavPath)
		{
			if (NavPath->PathPoints.Num()<=0)return;
			FVector Destination= NavPath->PathPoints.Last();
			CachedLocation=Destination;
			FVector DirToDest=(Destination-GetPawn()->GetActorLocation()).GetSafeNormal();
			GetPawn()->AddMovementInput(DirToDest,1);
		}
		if (NavPath)
		{
			SplineComponent->ClearSplinePoints();
			for (auto Pnt:NavPath->PathPoints)
			{
				SplineComponent->AddSplinePoint(Pnt,ESplineCoordinateSpace::World);
				UKismetSystemLibrary::DrawDebugSphere(this,Pnt);
			}
		}
	}
}

void AMyPlayerController::InputReleasedFunc(FGameplayTag InputTag)
{
	FString String=InputTag.ToString();
	// UKismetSystemLibrary::PrintString(this,String+FString("Released"));
	if (HeldTime>ShortPressThreshold)
	{
		bIsAutoRunning=true;
	}
}

void AMyPlayerController::AutoMove()
{
	if (!bIsAutoRunning) return;
	float Distance= (GetPawn()->GetActorLocation()-CachedLocation).Length();
	if (Distance<DistanceThreshold)
	{
		bIsAutoRunning=false;
	}
	else
	{
		FVector Direction=SplineComponent->FindTangentClosestToWorldLocation(GetPawn()->GetActorLocation(),ESplineCoordinateSpace::World);
		GetPawn()->AddMovementInput(Direction,1);
	}
}


void AMyPlayerController::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility,false,HitResult);
	LastActor=ThisActor;
	if (HitResult.bBlockingHit)
	{
		ThisActor= Cast<ICursorHitInterface>(HitResult.GetActor());
	}
	if (ThisActor && ThisActor!=LastActor)
	{
		ThisActor->Highlight();
	}
	if (LastActor && LastActor!=ThisActor)
	{
		LastActor->UnHighlight();
	}
}

