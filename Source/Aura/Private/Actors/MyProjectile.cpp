// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/MyProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Aura/Aura.h"
#include "Components/AudioComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AMyProjectile::AMyProjectile()
{
	PrimaryActorTick.bCanEverTick=false;
	bReplicates=true;
	SphereComponent=CreateDefaultSubobject<USphereComponent>("SphereComponent");
	SphereComponent->SetCollisionObjectType(ECC_Projectile);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic,ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	
	ProjectileMovementComp=CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComp->InitialSpeed=550.f;
	ProjectileMovementComp->MaxSpeed=550.f;
	ProjectileMovementComp->ProjectileGravityScale=0.f;

}

// Called when the game starts or when spawned
void AMyProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&ThisClass::OnSphereOverlapCallBack);

	LoopingSoundComponent=UGameplayStatics::SpawnSoundAttached(LoopingSound,GetRootComponent());
}

void AMyProjectile::OnSphereOverlapCallBack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{

	UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
	LoopingSoundComponent->Stop();
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetAsc=UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetAsc->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
			TargetAsc->ApplyGameplayEffectSpecToSelf(*HitReactEffectSpecHandle.Data.Get());
		}
		Destroy();
	}
	else
	{
		bHit=true;
	}
	
}

void AMyProjectile::Destroyed()
{
	if (!bHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this,ImpactSound,GetActorLocation());
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ImpactEffect,GetActorLocation());
		LoopingSoundComponent->Stop();
	}
	Super::Destroyed();
}


