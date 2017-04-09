// Copyright Anurag Sharma 2017

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor();
	void CloseDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
		float OpenAngle = 80.0f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	AActor* ActorThatOpens;

	UPROPERTY(VisibleAnywhere)
		FRotator InitialAngle;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 0.65f;

	float LastDoorOpenTime;
	AActor* Owner;
};