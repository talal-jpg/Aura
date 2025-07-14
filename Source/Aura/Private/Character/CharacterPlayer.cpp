// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterPlayer.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MyPlayerState.h"

ACharacterPlayer::ACharacterPlayer()
{
	Camera=CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraArm= CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	Camera->SetupAttachment(CameraArm);
	CameraArm->SetupAttachment(GetRootComponent());
}

void ACharacterPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfoAndSetASCASMemberVars();
}

void ACharacterPlayer::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityActorInfoAndSetASCASMemberVars();
}

void ACharacterPlayer::InitAbilityActorInfoAndSetASCASMemberVars()
{
	AbilitySystemComponent= GetPlayerState<AMyPlayerState>()->GetAbilitySystemComponent();
	AbilitySystemComponent->InitAbilityActorInfo(GetPlayerState<AMyPlayerState>(),this);
	AttributeSet= GetPlayerState<AMyPlayerState>()->AttributeSet;
}
