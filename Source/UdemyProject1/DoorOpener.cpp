// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpener.h"

UDoorOpener::UDoorOpener()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
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

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}
	
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

