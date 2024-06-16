// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* physicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if(physicsHandle != nullptr) { UE_LOG(LogTemp, Display, TEXT("COMPONENT NAME: %s"), *physicsHandle->GetName()); }
	else { UE_LOG(LogTemp, Error, TEXT("NO COMPONENT TO POINT TO!")); }
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Display, TEXT("GRAB BUTTON PRESSED."));

	FVector lineStart = GetComponentLocation();
	FVector lineEnd = lineStart + (GetForwardVector() * grabDistance);
	DrawDebugLine(GetWorld(), lineStart, lineEnd, FColor::Red);
	FHitResult hitResult;

	bool grabbableFound = GetWorld()->SweepSingleByChannel(
							hitResult,
							lineStart,
							lineEnd,
							FQuat::Identity,
							ECC_GameTraceChannel2,
							FCollisionShape::MakeSphere(grabRadius));
	
	if(grabbableFound)
	{
		DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);
		UE_LOG(LogTemp, Display, TEXT("OBJECT HIT: %s"), *hitResult.GetActor()->GetActorNameOrLabel());
	}
	else { UE_LOG(LogTemp, Display, TEXT("NO OBJECT HIT.")); }
}

void UGrabber::Release()
{
	
	UE_LOG(LogTemp, Display, TEXT("GRAB BUTTON RELEASED."));
}