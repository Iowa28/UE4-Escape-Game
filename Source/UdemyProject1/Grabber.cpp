// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"

#include "DrawDebugHelpers.h"

#define OUT

UGrabber::UGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UGrabber::BeginPlay()
{
	Super::BeginPlay();
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// UE_LOG(
	// 	LogTemp, Warning, TEXT("Location: %s, %s"),
	// 	*PlayerViewPointLocation.ToString(),
	// 	*PlayerViewPointRotation.ToString()
	// );

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// DrawDebugLine(
	// 	GetWorld(),
	// 	PlayerViewPointLocation,
	// 	LineTraceEnd,
	// 	FColor(0, 255, 0),
	// 	false,
	// 	0.f,
	// 	0.f,
	// 	10.f
	// );

	FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		TraceParameters
	);

	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Name: %s"), *ActorHit->GetName());
	}
}

