// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Data/DA_AttributeInfo.h"

FAttributeInfo UDA_AttributeInfo::FindInfoForTag(FGameplayTag AttributeTag)
{
	for (auto AttributeInfo : AttributeInfoArray)
	{
		if (AttributeInfo.AttributeTag == AttributeTag)
		{
			return AttributeInfo;
		}
	}
	return FAttributeInfo();
}
