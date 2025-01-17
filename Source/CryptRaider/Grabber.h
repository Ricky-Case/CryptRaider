#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Grab();

private:
	UPhysicsHandleComponent* GetPhysicsHandle() const;
	bool GetGrabbableInReach(FHitResult&);

	void GrabObject(FHitResult&, UPhysicsHandleComponent*);
	void ReleaseObject(FHitResult&, UPhysicsHandleComponent*);

	UPROPERTY(EditAnywhere)
	float grabDistance = 200.0f;

	UPROPERTY(EditAnywhere)
	float grabRadius = 100.0f;

	UPROPERTY(EditAnywhere)
	float holdDistance = 200.0f;

	bool grabbed;
	FString componentName = "";
};
