// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	WeaponMesh=CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh(),FName("HandSocket"));

	Camera=CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraArm= CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	Camera->SetupAttachment(CameraArm);
	CameraArm->SetupAttachment(GetRootComponent());
}




