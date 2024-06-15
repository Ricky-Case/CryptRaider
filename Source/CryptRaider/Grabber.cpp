// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

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
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

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
		UE_LOG(LogTemp, Display, TEXT("OBJECT IN RANGE: %s"), *hitResult.GetActor()->GetActorNameOrLabel());
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("NO OBJECT IN RANGE."));
	}
}