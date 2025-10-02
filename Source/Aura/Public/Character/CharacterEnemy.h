// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Character/CharacterBase.h"
#include "Components/WidgetComponent.h"
#include "GAS/Data/DA_DefaultEnemyAttributes.h"
#include "Interface/CursorHitInterface.h"
#include "CharacterEnemy.generated.h"

class AMyAIController;
class UBehaviorTree;
struct FGameplayTag;
class UMyUserWidget;
enum class ECharacterClass : uint8;
class UGameplayEffect;

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeBroadcastNewValDelegateSignature, float , NewVal);
UCLASS(BlueprintType)
class AURA_API ACharacterEnemy : public ACharacterBase , public ICursorHitInterface ,public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ACharacterEnemy();

	virtual void PossessedBy(AController* NewController) override;

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
	virtual void Highlight() override;
	virtual void UnHighlight() override;

	UPROPERTY(BlueprintReadWrite)
	bool bIsHighlighted;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float BaseWalkSpeed=500.f;

	UPROPERTY(EditAnywhere)
	ECharacterClass CharacterClass=ECharacterClass::Warrior;

	void ApplyEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float Level=1;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeBroadcastNewValDelegateSignature OnHealthChangeBroadcastNewValDelegate;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeBroadcastNewValDelegateSignature OnMaxHealthChangeBroadcastNewValDelegate;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Widget")
	UWidgetComponent* HealthBarWidgetComp;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Widget")
	UMyUserWidget* HealthBarUserWidget;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable)
	void BroadcastInitialValues();

	void HitReactTagChanged(const FGameplayTag, int32 NewCount);
	
	bool bHitReacting=false;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AMyAIController> MyAIController;

	UPROPERTY()
	AActor* CombatTarget=nullptr;

	virtual AActor* GetCombatTarget_Implementation() override;

	virtual void SetCombatTarget_Implementation(AActor* NewCombatTarget) override;

	virtual void Die() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float LifeSpan=5.f;
};
