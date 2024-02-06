// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpener.h"

#define OUT

UDoorOpener::UDoorOpener()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
}

void UDoorOpener::OpenDoor() const
{
	const FRotator NewRotation = FRotator(0.f, OpenAngle, 0.f);
	Owner->SetActorRotation(NewRotation);
}

void UDoorOpener::CloseDoor() const
{
	const FRotator NewRotation = FRotator(0.f, 0.f, 0.f);
	Owner->SetActorRotation(NewRotation);
}


void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOfActorsOnPlate() > 25.f)
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

float UDoorOpener::GetTotalMassOfActorsOnPlate() const
{
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	for (const AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}

