// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "MyProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraSystem;

UCLASS()
class AURA_API AMyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* ProjectileMovementComp;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USphereComponent* SphereComponent;

	UFUNCTION()
	void OnSphereOverlapCallBack(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY( EditAnywhere)
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY( EditAnywhere)
	TObjectPtr<USoundBase> ImpactSound;

	bool bHit=false;

	virtual void Destroyed() override;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> LoopingSound;
	
	UPROPERTY()
	TObjectPtr<UAudioComponent> LoopingSoundComponent;

	UPROPERTY(EditAnywhere)
	float LifeSpan=15.f;

	
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	
	FGameplayEffectSpecHandle HitReactEffectSpecHandle;
};
