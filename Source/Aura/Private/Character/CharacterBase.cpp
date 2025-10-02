// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Components/CapsuleComponent.h"
#include "GAS/MyAbilitySystemComponent.h"
#include "GAS/GameplayAbility/MyGameplayAbility.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
	WeaponMesh=CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	WeaponMesh->SetupAttachment(GetMesh(),FName("HandSocket"));

}

FVector ACharacterBase::GetSocketLocation_Implementation(FName SocketName)
{
	return WeaponMesh->GetSocketLocation(SocketName);
}


// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAnimMontage* ACharacterBase::GetHitReactMontage_Implementation()
{
	return HitReactMontage;
}

FTaggedMontage ACharacterBase::GetTaggedAttackMontageStruct_Implementation()
{
	int32 NumElems=TaggedAttackMontages.Num();
	FTaggedMontage TaggedMontage;
	
	for(int32 i=0;i<NumElems-1;i++)
	{
		int32 RandNum= FMath::RandRange(0,NumElems-1);
		TaggedMontage= TaggedAttackMontages[RandNum];
	}
	return  TaggedMontage;
}



void ACharacterBase::InitializeDefaultAttributes()
{
}



void ACharacterBase::GiveStartupAbilities()
{
	Cast<UMyAbilitySystemComponent>(AbilitySystemComponent)->AddStartupAbilities(StartupAbilities);
}

void ACharacterBase::Die()
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld,true));
	MulticastHandleDeath();
}

void ACharacterBase::MulticastHandleDeath_Implementation()
{
	WeaponMesh->SetSimulatePhysics(true);
	WeaponMesh->SetEnableGravity(true);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}