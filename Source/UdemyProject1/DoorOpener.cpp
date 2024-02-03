// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorOpener.h"

UDoorOpener::UDoorOpener()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();
}

void UDoorOpener::OpenDoor() const
{
	AActor* Owner = GetOwner();
	FRotator Rotation = Owner->GetActorRotation();
	Rotation.Add(0.f, OpenAngle, 0.f);
	Owner->SetActorRotation(Rotation);
}


void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
	}
}

