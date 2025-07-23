// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/Data/AttributeInfoDataAsset.h"

#include "Kismet/KismetSystemLibrary.h"

FAttributeInfoStruct UAttributeInfoDataAsset::GetAttributeInfoByTag(FGameplayTag Tag)
{
	for (auto AttribInfo:AttributeInfo)
	{
		if (AttribInfo.AttributeGameplayTag== Tag)
		{
			return AttribInfo;
		}
	}
		return FAttributeInfoStruct();
}
