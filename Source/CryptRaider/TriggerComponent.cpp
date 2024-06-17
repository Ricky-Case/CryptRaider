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

	for(AActor* actor : overlappingActors) { UE_LOG(LogTemp, Warning, TEXT("OVERLAP WITH ACTOR: %s"), *actor->GetActorNameOrLabel()); }
}