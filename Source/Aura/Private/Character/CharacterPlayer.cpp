// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MyPlayerController.h"
#include "Player/MyPlayerState.h"
#include "UI/MyHUD.h"
#include "UI/WidgetController/MyWidgetController.h"


ACharacterPlayer::ACharacterPlayer()
{
	Camera=CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraArm= CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	Camera->SetupAttachment(CameraArm);
	CameraArm->SetupAttachment(GetRootComponent());
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	if (!HasAuthority())
	{
	}
}

int ACharacterPlayer::GetPlayerLevel()
{
	return PlayerLevel;
}

void ACharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfoAndSetASCASMemberVars();
	// GiveStartUpAbilities();
}

void ACharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfoAndSetASCASMemberVars();
	// GiveStartUpAbilities();
	
}

void ACharacterPlayer::InitAbilityActorInfoAndSetASCASMemberVars()
{
	AMyPlayerState* PS=GetPlayerState<AMyPlayerState>();	
	AbilitySystemComponent= PS->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(GetPlayerState<AMyPlayerState>(),this);
	AttributeSet= PS->AttributeSet;

	// initAttributes
	
	InitializePrimaryAttributes();
	InitializeSecondaryAttributes();
	InitializeVitalAttributes();
	
	APlayerController* PC= GetController<AMyPlayerController>();
	FWidgetControllerParams WCParams= FWidgetControllerParams(PC,PS,AbilitySystemComponent,AttributeSet);
	if (PC)// have to check PC with an if here because only on server all the PCs are present and on all the clients every client only has one 
	{
		if (AMyHUD* MyHUD=PC->GetHUD<AMyHUD>())
		{
			MyHUD->InitOverlay(WCParams);
			
		}
	}
}


void ACharacterPlayer::GiveStartUpAbilities()
{
	for (auto Ability : StartUpAbilities)
	{
		FGameplayAbilitySpec AbilitySpec=AbilitySystemComponent->BuildAbilitySpecFromClass(Ability);
		FGameplayAbilitySpecHandle AbilitySpecHandle=AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

