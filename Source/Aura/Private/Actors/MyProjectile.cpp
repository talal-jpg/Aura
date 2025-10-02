// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MyProjectile.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyProjectile::AMyProjectile()
{
	ProjectileSphere= CreateDefaultSubobject<USphereComponent>("SphereComponent");
	ProjectileSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileSphere->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	ProjectileSphere->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	ProjectileSphere->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	
	ProjectileMovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed=400;
	ProjectileMovementComponent->MaxSpeed=550;
	ProjectileMovementComponent->ProjectileGravityScale=0;

}


// Called when the game starts or when spawned
void AMyProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileSphere->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::AMyProjectile::OnSphereOverlapCallBack);
	
	
}
void AMyProjectile::OnSphereOverlapCallBack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::PlaySoundAtLocation(this,HitSound,OtherActor->GetActorLocation());
	IAbilitySystemInterface* ASI=Cast<IAbilitySystemInterface>(OtherActor);
	if (ASI)
	{
		ASI->GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(DamageGESpec);
	}
	Destroy();
}
