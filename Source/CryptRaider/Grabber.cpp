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

	if(physicsHandle && physicsHandle->GetGrabbedComponent())
	{
		physicsHandle->SetTargetLocationAndRotation(
			GetComponentLocation() + GetForwardVector() * holdDistance,
			GetComponentRotation() //TODO: Rotate object upright.
		);
	}
}


void UGrabber::Grab()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();

	if(physicsHandle)
	{
		FHitResult hitResult;
		bool grabbableFound = GetGrabbableInReach(hitResult);
		
		if(grabbed) { ReleaseObject(hitResult, physicsHandle); }
		else { if(grabbableFound) { GrabObject(hitResult, physicsHandle); } }
	}
}


UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	return result;
}


bool UGrabber::GetGrabbableInReach(FHitResult& hitResult)
{
	FVector lineStart = GetComponentLocation();
	FVector lineEnd = lineStart + (GetForwardVector() * grabDistance);
	
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
	UPrimitiveComponent* hitComponent = hitResult.GetComponent();
	componentName = hitComponent->GetName();

	hitComponent->SetSimulatePhysics(true);
	hitComponent->WakeAllRigidBodies();

	AActor* hitActor = hitResult.GetActor();
	hitActor->Tags.Add("Grabbed");
	hitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	physicsHandle->GrabComponentAtLocationWithRotation(
		hitComponent,
		NAME_None,
		hitResult.ImpactPoint,
		GetComponentRotation()
	);

	grabbed = true;
}


void UGrabber::ReleaseObject(FHitResult& hitResult, UPhysicsHandleComponent* physicsHandle)
{
	hitResult.GetActor()->Tags.Remove("Grabbed");

	physicsHandle->ReleaseComponent();
	grabbed = false;
}