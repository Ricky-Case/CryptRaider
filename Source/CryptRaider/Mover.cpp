#include "Mover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UMover::UMover()
{
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

	if(moveSpeed < 0) { moveSpeed *= -1; }
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bMove)
	{
		FVector currentLocation = GetOwner()->GetActorLocation();
		FVector newLocation = FMath::VInterpConstantTo(currentLocation, targetLocation, DeltaTime, moveSpeed);
		GetOwner()->SetActorLocation(newLocation);
	}
	else
	{
		FVector currentLocation = GetOwner()->GetActorLocation();
		FVector newLocation = FMath::VInterpConstantTo(currentLocation, startLocation, DeltaTime, moveSpeed);
		GetOwner()->SetActorLocation(newLocation);
	}
}


void UMover::SetMove(bool bShouldMove) { bMove = bShouldMove; }

FString UMover::GetMoveValue() const
{
	if(bMove) { return "TRUE"; }
	else { return "FALSE"; }
}