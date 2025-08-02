// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMCs/MMC_MaxHealth.h"

#include "AbilitySystem/MyAttributeSet.h"
#include "Interface/CombatInterface.h"
#include "Kismet/KismetSystemLibrary.h"

UMMC_MaxHealth::UMMC_MaxHealth(const FObjectInitializer& InitializerModule)
{
	VigorDef.AttributeSource=EGameplayEffectAttributeCaptureSource::Source;
	VigorDef.AttributeToCapture=UMyAttributeSet::GetVigorAttribute();
	VigorDef.bSnapshot=false;
	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer SourceTags= GetSourceAggregatedTags(Spec);
	FGameplayTagContainer TargetTags = GetTargetAggregatedTags(Spec);
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags=&SourceTags;
	EvaluateParameters.TargetTags=&SourceTags;

	float VigorMagnitude = 0;
	GetCapturedAttributeMagnitude(VigorDef,Spec,EvaluateParameters,VigorMagnitude);

	ICombatInterface* CombatInterface=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int PlayerLevel=CombatInterface->GetPlayerLevel();
	return VigorMagnitude*(PlayerLevel*2.5);
}
