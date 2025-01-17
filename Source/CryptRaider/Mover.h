#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Mover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetMove(bool);
	
	FString GetMoveValue() const;

private:
	UPROPERTY(EditAnywhere)
	FVector moveOffset;

	UPROPERTY(EditAnywhere)
	float moveTime = 4.0f;

	UPROPERTY(EditAnywhere)
	bool bMove = false;

	FVector startLocation;
	FVector targetLocation;
	float moveSpeed;
};
