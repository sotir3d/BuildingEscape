// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	OwnerOpeningDoor = GetOwner();
	// Get the Player-Pawn
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenDoor::OpenDoor()
{
	OwnerOpeningDoor->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	OwnerOpeningDoor->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the TriggerVolume every frame
	// if the ActorThatOpens is in the volume then open the door
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	//Check if it's Time to close the door
	if ((LastDoorOpenTime + DoorCloseDelay) <= GetWorld()->GetTimeSeconds())
	{
		CloseDoor();
	}
	
}

