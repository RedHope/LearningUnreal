// Copyright Anurag Sharma 2017

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
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

private:
	AActor* Owner;		
	APlayerController* PlayerController;
	float Reach = 100.0f;
	void Grab();
	void EndGrab();
	void FindPhysicsHandleComponent();
	void AttachInputHandlers();
	void GDrawDebugLine(FRotator, FVector, FVector);
	const FHitResult GetFirstHitResult(FRotator, FVector, FVector);

	UPhysicsHandleComponent *PhysicsHandle = nullptr;
	UInputComponent *InputComponent = nullptr;
};
