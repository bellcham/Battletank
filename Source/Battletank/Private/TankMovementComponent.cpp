// Fill out your copyright notice in the Description page of Project Settings.

#include "Battletank.h"
#include "../Public/TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!LeftTrackToSet || !RightTrackToSet) { return; }
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%f: IntendMoveForward Throw: %f"), GetWorld()->GetTimeSeconds(), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendMoveClockwise(float Throw)
{
	auto TankName = GetOwner()->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%f: IntendMoveClockwise Throw: %f"), GetWorld()->GetTimeSeconds(), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-1.f * Throw);
}