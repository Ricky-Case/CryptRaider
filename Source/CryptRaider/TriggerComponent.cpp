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

	if(mover == nullptr) { return; }

	AActor* unlocker = GetUnlocker();

	if(unlocker != nullptr)
	{
		UPrimitiveComponent* component = Cast<UPrimitiveComponent>(unlocker->GetRootComponent());
		
		if (component != nullptr) { component->SetSimulatePhysics(false); }
		
		unlocker->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
		mover->SetMove(true);
	}
	else
	{
		mover->SetMove(false);
	}
}

void UTriggerComponent::SetMover(UMover* newMover) { mover = newMover; }

AActor* UTriggerComponent::GetUnlocker() const
{
	TArray<AActor*> overlappingActors;
	GetOverlappingActors(overlappingActors);

	for(AActor* actor : overlappingActors) { if(actor->ActorHasTag(unlockTag)) { return actor; } }

	return nullptr;
}