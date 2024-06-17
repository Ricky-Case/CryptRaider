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

	AActor* unlocker = GetUnlocker();

	if(unlocker != nullptr) { UE_LOG(LogTemp, Display, TEXT("Door Unlocked.")); }
	else { UE_LOG(LogTemp, Display, TEXT("Door Locked.")); }
}

AActor* UTriggerComponent::GetUnlocker() const
{
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors);

	for(AActor* actor : overlappingActors) { if(actor->ActorHasTag(unlockTag)) { return actor; } }

	return nullptr;
}