// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActiveGameplayEffectHandle.h"
#include "MyEffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(Blueprintable)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap UMETA(DisplayName = "ApplyOnOverlap"),
	ApplyOnEndOverlap UMETA(DisplayName = "ApplyOnEndOverlap"),
	DoNotApply UMETA(DisplayName = "DonotApply"),
	
};
UENUM(Blueprintable)
enum class EEffectRemovalPolicy:uint8
{
	RemoveOnOverlap UMETA(DisplayName = "RemoveOnOverlap"),
	RemoveOnEndOverlap UMETA(DisplayName = "RemoveOnEndOverlap")
};

UENUM(Blueprintable)
enum class EEffectDurationType : uint8
{
	InstantEffect UMETA(DisplayName = "InstantEffect"),
	DurationEffect UMETA(DisplayName = "DurationEffect"),
	InfiniteEffect UMETA(DisplayName = "InfiniteEffect")
};

UCLASS()
class AURA_API AMyEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditAnywhere)
	TObjectPtr<USceneComponent> MyRootComponent;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* OtherActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* OtherActor);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GE")
	TSubclassOf<UGameplayEffect> GameplayEffectClass;


	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GE")
	EEffectApplicationPolicy EffectApplicationPolicy;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "GE")
	EEffectRemovalPolicy EffectRemovalPolicy;


	UPROPERTY(BlueprintReadWrite)
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveGameplayEffectHandles;

};
