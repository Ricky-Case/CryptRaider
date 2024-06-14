// Fill out your copyright notice in the Description page of Project Settings.


#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetOwner()->GetActorLocation();
	targetLocation = startLocation + moveOffset;
	moveSpeed = ( FMath::Sqrt(
							  (targetLocation.X * targetLocation.X)
							+ (targetLocation.Y * targetLocation.Y)
							+ (targetLocation.Z * targetLocation.Z)
				  )
				- FMath::Sqrt((startLocation.X * startLocation.X)
							+ (startLocation.Y * startLocation.Y)
							+ (startLocation.Z * startLocation.Z)
				  )
				) / moveTime;
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(moveNow)
	{
		FVector currentLocation = GetOwner()->GetActorLocation();
		FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, moveSpeed);
		GetOwner()->SetActorLocation(newLocation);
	}
}

