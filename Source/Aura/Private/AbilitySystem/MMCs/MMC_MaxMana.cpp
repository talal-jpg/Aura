// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/MMCs/MMC_MaxMana.h"

#include "AbilitySystem/MyAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelDef.AttributeSource=EGameplayEffectAttributeCaptureSource::Source;
	IntelDef.AttributeToCapture=UMyAttributeSet::GetIntelligenceAttribute();
	IntelDef.bSnapshot=false;

	RelevantAttributesToCapture.Add(IntelDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	FGameplayTagContainer SourceTags= GetSourceAggregatedTags(Spec);
	FGameplayTagContainer TargetTags= GetTargetAggregatedTags(Spec);
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags= &SourceTags;
	EvaluateParameters.TargetTags= &TargetTags;
	float IntelMagnitude = 0.0f;
	GetCapturedAttributeMagnitude(IntelDef,Spec,EvaluateParameters,IntelMagnitude);

	ICombatInterface* CombatInterface=Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	int PlayerLevel=CombatInterface->GetPlayerLevel();

	return IntelMagnitude*(PlayerLevel*2.5);
}
