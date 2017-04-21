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
	FindPhysicsHandleComponent();
	// Look for physics handle
	AttachInputHandlers();
}

void UGrabber::AttachInputHandlers()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Found input handler on %s"), *GetOwner()->GetName());
		// Bind the input action
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::EndGrab);
	}
}

// Draws a debug line on call
void UGrabber::GDrawDebugLine(FRotator ActorRotator, FVector ActorLocation, FVector LineTracker)
{
	DrawDebugLine(GetWorld(), ActorLocation, LineTracker, FColor(255, 0, 0), false, -1, 0, 0.33);
}

// Line trace to reach distance.
const FHitResult UGrabber::GetFirstHitResult(FRotator ActorRotator, FVector ActorLocation, FVector LineTracker)
{
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

	return LineTraceHit;
}

void UGrabber::FindPhysicsHandleComponent() {
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found Physics handler on %s"), GetOwner())
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No physics handler found on player. Add physics handler to %s"), *GetOwner()->GetName());
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
	GDrawDebugLine(ActorRotator, ActorLocation, LineTracker);
	GetFirstHitResult(ActorRotator, ActorLocation, LineTracker);
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("I am trying to grab things."));

	// Try to reach actors with PhysicsBody collision channel
	// TODO: Attach physics handle
}

void UGrabber::EndGrab()
{
	UE_LOG(LogTemp, Warning, TEXT("End grab"));
	// TODO: Release physics
}

