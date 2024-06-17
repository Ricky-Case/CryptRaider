// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"


UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	grabbed = false;
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	if(physicsHandle == nullptr) { return; }

	if(physicsHandle->GetGrabbedComponent() != nullptr)
	{
		physicsHandle->SetTargetLocationAndRotation(
			GetComponentLocation() + GetForwardVector() * holdDistance,
			GetComponentRotation() //TODO: Rotate object upright.
		);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Display, TEXT("INTERACT BUTTON PRESSED."));

	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	if(physicsHandle == nullptr) { return; }

	FHitResult hitResult;
	bool grabbableFound = GetGrabbableInReach(hitResult);
	
	if(grabbed)
	{
		ReleaseObject(hitResult, physicsHandle);
	}
	else
	{
		if(grabbableFound)
		{
			GrabObject(hitResult, physicsHandle);
		}
	}
}


UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if(result == nullptr) { UE_LOG(LogTemp, Warning, TEXT("GRABBER REQUIRES UPhysicsHandleComponent!")); }

	return result;
}


bool UGrabber::GetGrabbableInReach(FHitResult& hitResult)
{
	FVector lineStart = GetComponentLocation();
	FVector lineEnd = lineStart + (GetForwardVector() * grabDistance);
	DrawDebugLine(GetWorld(), lineStart, lineEnd, FColor::Red);

	bool grabbableFound = GetWorld()->SweepSingleByChannel(
		hitResult,
		lineStart,
		lineEnd,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(grabRadius)
	);

	return grabbableFound;
}

void UGrabber::GrabObject(FHitResult& hitResult, UPhysicsHandleComponent* physicsHandle)
{
	DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10, 10, FColor::Green, false, 5);
	UPrimitiveComponent* hitComponent = hitResult.GetComponent();
	componentName = hitComponent->GetName();

	hitComponent->WakeAllRigidBodies();

	hitResult.GetActor()->Tags.Add("Grabbed");

	physicsHandle->GrabComponentAtLocationWithRotation(
		hitComponent,
		NAME_None,
		hitResult.ImpactPoint,
		GetComponentRotation()
	);

	UE_LOG(LogTemp, Display, TEXT("GRABBED: %s."), *componentName);
	grabbed = true;
}

void UGrabber::ReleaseObject(FHitResult& hitResult, UPhysicsHandleComponent* physicsHandle)
{
	DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 10, 10, FColor::Blue, false, 5);
	UE_LOG(LogTemp, Display, TEXT("DROPPED: %s."), *componentName);
	
	hitResult.GetActor()->Tags.Remove("Grabbed");

	physicsHandle->ReleaseComponent();
	grabbed = false;
}