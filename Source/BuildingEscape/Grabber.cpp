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

	// Look for physics handle

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Physics handler on %s"), GetOwner())
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No physics handler found on player. Add physics handler to %s"), *GetOwner()->GetName());
	}

	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Found input handler on %s"), *GetOwner()->GetName());
		// Bind the input action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::EndGrab);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No input handler found on player. Add input handler to %s"), *GetOwner()->GetName());
	}
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

	FVector LineTracker = ActorLocation + ActorRotator.Vector() * Reach;

	DrawDebugLine(GetWorld(), ActorLocation, LineTracker, FColor(255, 0, 0), false, -1, 0, 0.33);

	// Line trace to reach distance.

	FHitResult LineTraceHit;
	FCollisionObjectQueryParams ObjectQueryParams{
		ECollisionChannel::ECC_PhysicsBody
	};
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	bool bIsHitFound = GetWorld()->LineTraceSingleByObjectType(
		LineTraceHit,
		ActorLocation,
		LineTracker,
		ObjectQueryParams,
		TraceParams
	);

	if (bIsHitFound) {
		FString ActorName = LineTraceHit.GetActor()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Actor hit %s"), *ActorName);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("I am trying to grab things."));
}

void UGrabber::EndGrab()
{
	UE_LOG(LogTemp, Warning, TEXT("End grab"));
}

