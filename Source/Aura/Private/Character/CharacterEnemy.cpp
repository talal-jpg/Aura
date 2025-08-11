// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterEnemy.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagsManager.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "AbilitySystem/MyBlueprintFunctionLibrary.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/MyUserWidget.h"

ACharacterEnemy::ACharacterEnemy()
{
	AbilitySystemComponent=CreateDefaultSubobject<UMyAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet= CreateDefaultSubobject<UMyAttributeSet>("AttributeSet");
	WidgetComponent=CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);
}

void ACharacterEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);

	GetCharacterMovement()->MaxWalkSpeed= BaseWalkSpeed;

	HealthBar= Cast<UMyUserWidget>(WidgetComponent->GetWidget());
	if (HealthBar)
	{
		HealthBar->SetWidgetController(this);
	}
	UMyAttributeSet* MyAttributeSet= Cast<UMyAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			float Val=Data.NewValue;
			OnHealthChangeDelegate.Broadcast(Val);
		}
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(MyAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			float Val=Data.NewValue;
			OnMaxHealthChangeDelegate.Broadcast(Val);
		}
	);

	FGameplayTag Effects_HitReact=UGameplayTagsManager::Get().RequestGameplayTag("Effects.HitReact");
	AbilitySystemComponent->RegisterGameplayTagEvent(Effects_HitReact,EGameplayTagEventType::AnyCountChange).AddUObject(this,&ThisClass::HitReactGameplayTagChangedDelegateCallback);
	
	InitializeDefaultAttributes();
	GiveStartUpAbilities();
	
}

int ACharacterEnemy::GetPlayerLevel()
{
	return PlayerLevel;
}

void ACharacterEnemy::InitializeDefaultAttributes()
{
	UMyBlueprintFunctionLibrary::InitializeDefaultCharacterAttributes(this,CharacterClass,Level,AbilitySystemComponent);
}

void ACharacterEnemy::HitReactGameplayTagChangedDelegateCallback(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting=NewCount>0;
	GetCharacterMovement()->MaxWalkSpeed=bHitReacting ? 0 : BaseWalkSpeed;

	if (bHitReacting)
	{
		AbilitySystemComponent->TryActivateAbilityByClass(HitReactAbilityClass);
	}
}

void ACharacterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float H=Cast<UMyAttributeSet>(AttributeSet)->GetHealth();
	float MaxH=Cast<UMyAttributeSet>(AttributeSet)->GetMaxHealth();
	
	
	// UKismetSystemLibrary::PrintString(this,AttributeSet->GetName());
	// UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("Health : %f"),H));
	// UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("MaxHealth : %f"),MaxH));
}

void ACharacterEnemy::Highlight()
{
	bIsHighlighted=true;
}

void ACharacterEnemy::UnHighlight()
{
	bIsHighlighted=false;
}
