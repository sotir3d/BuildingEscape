// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

#define OUT

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
	if (GetTotalMassOfActorsOnPlate() > 50.f) // TODO make into parameter
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

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;

	/// Find all the overlapping actors
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	/// Iterate through them adding weight
	for (auto *Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();

		UE_LOG(LogTemp, Warning, TEXT("%s on plate"), *Actor->GetName())
	}
	return TotalMass;
}