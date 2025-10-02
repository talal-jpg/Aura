// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterEnemy.h"

#include "AbilitySystemComponent.h"
#include "GameplayTagsManager.h"
#include "AI/MyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GAS/MyAbilitySystemComponent.h"
#include "GAS/MyAttributeSet.h"
#include "GAS/MyBlueprintFunctionLibrary.h"
#include "GAS/Data/DA_DefaultEnemyAttributes.h"
#include "Kismet/GameplayStatics.h"

ACharacterEnemy::ACharacterEnemy()
{
	AbilitySystemComponent=CreateDefaultSubobject<UMyAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet=CreateDefaultSubobject<UMyAttributeSet>("AttributeSet");
	
	HealthBarWidgetComp= CreateDefaultSubobject<UWidgetComponent>("HealthBarWidgetComp");
	
	HealthBarWidgetComp->SetupAttachment(GetRootComponent());
	
	GetCharacterMovement()->MaxWalkSpeed= BaseWalkSpeed;
	
}

void ACharacterEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (!HasAuthority()) return;
	MyAIController= Cast<AMyAIController>(NewController);

	MyAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	MyAIController->RunBehaviorTree(BehaviorTree);
	bool bIsRanged= CharacterClass== ECharacterClass::Warrior ? false:true;
	MyAIController->GetBlackboardComponent()->SetValueAsBool(FName("bIsRanged"),bIsRanged);
	
}

void ACharacterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACharacterEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	UMyBlueprintFunctionLibrary::InitializeDefaultAttributes(CharacterClass,this,AbilitySystemComponent,Level);
	UMyBlueprintFunctionLibrary::GiveStartupAbilities(this,AbilitySystemComponent,CharacterClass);
	
	HealthBarUserWidget=Cast<UMyUserWidget>(HealthBarWidgetComp->GetWidget());
	if(HealthBarUserWidget)
	{
		HealthBarUserWidget->SetWidgetController(this);
	}
	else
	{
		UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("HealthBarWidget: NULL")));
	}
	UMyAttributeSet* AS= Cast<UMyAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			float NewVal=Data.NewValue;
			OnHealthChangeBroadcastNewValDelegate.Broadcast(NewVal);
		}
		);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AS->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			
			float NewVal= Data.NewValue;
			OnMaxHealthChangeBroadcastNewValDelegate.Broadcast(NewVal);
		}
		);
	FGameplayTag GameplayTag=UGameplayTagsManager::Get().RequestGameplayTag(FName("Effects.HitReact"));
	AbilitySystemComponent->RegisterGameplayTagEvent(GameplayTag,EGameplayTagEventType::NewOrRemoved).AddUObject(this,&ThisClass::HitReactTagChanged);
}

void ACharacterEnemy::Highlight()
{
	bIsHighlighted=true;
}

void ACharacterEnemy::UnHighlight()
{
	bIsHighlighted=false;
}


void ACharacterEnemy::ApplyEffect(TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	FGameplayEffectContextHandle EffectContextHandle=AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	FGameplayEffectSpecHandle EffectSpecHandle=AbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass,1,EffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

UAbilitySystemComponent* ACharacterEnemy::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterEnemy::BroadcastInitialValues()
{
	UMyAttributeSet* AS= Cast<UMyAttributeSet>(AttributeSet);
	OnHealthChangeBroadcastNewValDelegate.Broadcast(AS->GetHealth());
	OnMaxHealthChangeBroadcastNewValDelegate.Broadcast(AS->GetMaxHealth());
}

void ACharacterEnemy::HitReactTagChanged(const FGameplayTag, int32 NewCount)
{
	bHitReacting= NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed= bHitReacting ? 0 : BaseWalkSpeed;
}

AActor* ACharacterEnemy::GetCombatTarget_Implementation()
{
	return CombatTarget;
}

void ACharacterEnemy::SetCombatTarget_Implementation(AActor* NewCombatTarget)
{
	CombatTarget = NewCombatTarget;
}

void ACharacterEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}


// void ACharacterEnemy::InitializeDefaultAttributes()
// {
// 	ApplyEffect(DefaultPrimaryAttributes);
// 	ApplyEffect(DefaultSecondaryAttributes);
// 	ApplyEffect(DefaultVitalAttributes);
// 	// UGameplayStatics::GetGameMode(this)
// }

