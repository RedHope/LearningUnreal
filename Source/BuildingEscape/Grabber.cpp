// Copyright Anurag Sharma 2017

#include "BuildingEscape.h"
#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Owner = GetOwner();
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = GetWorld()->GetFirstPlayerController();
	// ...
	UE_LOG(LogTemp, Warning, TEXT("Reporting for duty!!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// Get Player viewpoint every tick.
	
	FRotator ActorRotator;
	FVector ActorLocation;
	
	PlayerController->GetPlayerViewPoint(ActorLocation, ActorRotator);

	UE_LOG(LogTemp, Warning, TEXT("Actor Location: %s, Actor Rotator: %s "), *ActorLocation.ToCompactString(), *ActorRotator.ToCompactString());
	
}

