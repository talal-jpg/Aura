// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterEnemy.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/MyAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UI/MyUserWidget.h"

ACharacterEnemy::ACharacterEnemy()
{
	AbilitySystemComponent=CreateDefaultSubobject<UMyAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet= CreateDefaultSubobject<UMyAttributeSet>("AttributeSet");
	WidgetComponent=CreateDefaultSubobject<UWidgetComponent>("WidgetComponent");
	WidgetComponent->SetupAttachment(RootComponent);

	HealthBar= Cast<UMyUserWidget>(WidgetComponent->GetWidget());
	
}

void ACharacterEnemy::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
	InitializePrimaryAttributes();
	InitializeSecondaryAttributes();
	InitializeVitalAttributes();
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
	
	
}

int ACharacterEnemy::GetPlayerLevel()
{
	return PlayerLevel;
}

void ACharacterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float H=Cast<UMyAttributeSet>(AttributeSet)->GetHealth();
	
	// UKismetSystemLibrary::PrintString(this,AttributeSet->GetName());
	UKismetSystemLibrary::PrintString(this,FString::Printf(TEXT("Health : %f"),H));
}

void ACharacterEnemy::Highlight()
{
	bIsHighlighted=true;
}

void ACharacterEnemy::UnHighlight()
{
	bIsHighlighted=false;
}
