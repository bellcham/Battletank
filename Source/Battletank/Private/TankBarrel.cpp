// Fill out your copyright notice in the Description page of Project Settings.

#include "Battletank.h"
#include "TankBarrel.h"




void UTankBarrel::MoveToElevation(float DesiredElevation)
{
	// Move barrel appropriate amount for frame based on max rotation rate.
	UE_LOG(LogTemp, Warning, TEXT("Barrel->MoveToPitch called with %f"), DesiredElevation);
	auto ClampedElevation = FMath::Clamp<float>(DesiredElevation, MinDegreesElevation, MaxDegreesElevation);
	auto ElevationError = ClampedElevation - RelativeRotation.Pitch;
	if (FMath::Abs(ElevationError) > 0.5)
	{
		auto ElevationChange = FMath::Sign(ElevationError) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
		SetRelativeRotation(FRotator(RelativeRotation.Pitch + ElevationChange, 0.f, 0.f));
	}
}