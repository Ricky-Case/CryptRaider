// Fill out your copyright notice in the Description page of Project Settings.

#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// UE_LOG(LogTemp, Warning, TEXT("GETTING OVERLAPPING ACTORS."));

	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors);

	if(overlappingActors.Num() > 0)
	{
		for(int32 index = 0; index < (overlappingActors.Num()); index++)
		{
			// FString actorName = overlappingActors[index]->GetActorNameOrLabel();
			// UE_LOG(LogTemp, Warning, TEXT("OVERLAP WITH ACTOR #%i: %s"), (index + 1), *actorName);

			UE_LOG(LogTemp, Warning, TEXT("OVERLAP WITH ACTOR #%i: %s"), (index + 1), *overlappingActors[index]->GetActorNameOrLabel());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("NO OVERLAPPING ACTORS."));
	}
}