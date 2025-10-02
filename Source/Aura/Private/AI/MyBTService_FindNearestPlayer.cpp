// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/MyBTService_FindNearestPlayer.h"

#include "AIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/GarbageCollectionSchema.h"

void UMyBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaTime)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaTime);

	APawn* OwningPawn=AIOwner->GetPawn();

	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");

	// UKismetSystemLibrary::PrintString(this,OwningPawn->GetName());
	
	TArray<AActor*> FoundActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn,TargetTag,FoundActorsWithTag);
	// if (FoundActorsWithTag.Num() <= 0)
	// {
	// 	UKismetSystemLibrary::PrintString(this,"notFound");
	// }
	// else
	// {
	// 	UKismetSystemLibrary::PrintString(this,FoundActorsWithTag[0]->GetName());
	// }

	FVector TargetLocation=FVector::ZeroVector;
	AActor* ClosestActor=nullptr;
	float DistanceToTarget=TNumericLimits<float>::Max();
	for (AActor* Actor : FoundActorsWithTag)
	{
		FVector ActorLoc=Actor->GetActorLocation();
		float ActorDist = (ActorLoc - OwningPawn->GetActorLocation()).Length();
		if (ActorDist<DistanceToTarget)
		{
			TargetLocation=ActorLoc;
			DistanceToTarget=ActorDist;
			ClosestActor=Actor;
			// GEngine->AddOnScreenDebugMessage(2,.5,FColor::Black,Actor->GetName());
		}
	}
	UBTFunctionLibrary::SetBlackboardValueAsObject(this,TargetToFollowSelector,ClosestActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this,DistanceToTargetSelector,DistanceToTarget);
}
