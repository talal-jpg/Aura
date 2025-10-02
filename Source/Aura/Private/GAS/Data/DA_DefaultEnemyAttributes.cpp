// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/Data/DA_DefaultEnemyAttributes.h"

#include <utility>

#include "UObject/GarbageCollectionSchema.h"

FCharacterClassInfo UDA_DefaultEnemyAttributes::GetInfoFromClass(ECharacterClass ClassToGet)
{
	for(auto pair : ClassToInfo)
	{
		if (pair.Key == ClassToGet)
		{
			return pair.Value;
		}
	}
	return FCharacterClassInfo();
}

FCharacterClassInfo* UDA_DefaultEnemyAttributes::GetCharacterClassInfo(ECharacterClass InCharacterClass)
{
	return ClassToInfo.Find(InCharacterClass);
}
