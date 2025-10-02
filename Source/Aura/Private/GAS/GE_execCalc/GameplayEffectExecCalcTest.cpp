// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/GE_execCalc/GameplayEffectExecCalcTest.h"

#include <string>

#include "AbilitySystemComponent.h"
#include "GAS/MyAttributeSet.h"
#include "Kismet/KismetSystemLibrary.h"

struct AuraDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor)
	AuraDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet,Armor,Target,false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UGameplayEffectExecCalcTest::UGameplayEffectExecCalcTest()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
}

void UGameplayEffectExecCalcTest::Execute_Implementation(
	const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);
	
	UAbilitySystemComponent* SourceASC=ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC=ExecutionParams.GetTargetAbilitySystemComponent();
	
	AActor* SourceActor=SourceASC ? SourceASC->GetAvatarActor(): nullptr;
	AActor* TargetActor=TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	
	
	const FGameplayEffectSpec& Spec=ExecutionParams.GetOwningSpec();

	// GetSetByCallerMagnitude
	// Spec.GetSetByCallerMagnitude()
	
	FAggregatorEvaluateParameters EvaluateParams;
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	EvaluateParams.SourceTags=SourceTags;
	EvaluateParams.TargetTags=TargetTags;
	float Armor=0;
	// if (DamageStatics().ArmorProperty)
	// {
	// 	FString Str=DamageStatics().ArmorDef.ToSimpleString();
	// 	UKismetSystemLibrary::PrintString(this,Str);
	// }
	// else
	// {
	// 	UKismetSystemLibrary::PrintString(this,FString("ArmorPropertyDefNotFound"));
	// }
		
	
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef,EvaluateParams,Armor);

	Armor+=100;
	
	FGameplayModifierEvaluatedData EvaluatedData=FGameplayModifierEvaluatedData(DamageStatics().ArmorProperty,EGameplayModOp::Additive,Armor);
	float Mag=EvaluatedData.Magnitude;
	// UKismetSystemLibrary::PrintString(this,std::to_string(Mag).data());
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

