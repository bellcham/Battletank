// Adam Bellchambers 2017

#include "Battletank.h"
#include "TankTurret.h"


void UTankTurret::MoveToAzimuth(float DesiredAzimuth)
{
	// Move Turret appropriate amount for frame based on max rotation rate.
	float DeltaTime = GetWorld()->DeltaTimeSeconds;
	float DeltaRate = MaxDegreesPerSecond * DeltaTime;
	float NewRotation = FMath::FixedTurn(RelativeRotation.Yaw, DesiredAzimuth, DeltaRate);
	SetRelativeRotation(FRotator(0.f, NewRotation, 0.f));

}

