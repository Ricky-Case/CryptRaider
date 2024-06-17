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

	if(mover == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("NO MOVER AVAILABLE!"));
		return;
	}

	AActor* unlocker = GetUnlocker();

	if(unlocker != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("STARTING MOVEMENT WITH MOVER AT: %i"), mover);
		mover->SetMove(true);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("STOPPING MOVEMENT WITH MOVER AT: %i"), mover);
		mover->SetMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* newMover)
{
	mover = newMover;
	UE_LOG(LogTemp, Display, TEXT("MOVER SET AT: %i"), mover);
	UE_LOG(LogTemp, Display, TEXT("TAKEN FROM NEW MOVER AT: %i"), newMover);
	if(mover == nullptr || newMover == nullptr) { UE_LOG(LogTemp, Error, TEXT("NULL POINTER ADDRESS")); }
}

AActor* UTriggerComponent::GetUnlocker() const
{
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors);

	for(AActor* actor : overlappingActors) { if(actor->ActorHasTag(unlockTag)) { return actor; } }

	return nullptr;
}