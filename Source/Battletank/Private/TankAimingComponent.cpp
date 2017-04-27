// Adam Bellchambers 2017

#include "Battletank.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "TankAimingComponent.h"


UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector TargetLocation, float FiringSpeed)
{
	if (!ensure(Barrel && Turret)) { return; }
	FVector SuggestedVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		GetOwner(), // TODO need to do aiming relative to tank rotation, not absolute??
		SuggestedVelocity,
		Barrel->GetSocketLocation(FName("Projectile")),
		TargetLocation,
		FiringSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if (bHaveAimSolution)
	{
		auto AimDirection = SuggestedVelocity.GetSafeNormal();
		Barrel->MoveToElevation(AimDirection.Rotation().Pitch);
		auto DesiredAzimuth = FMath::FindDeltaAngleDegrees(GetOwner()->GetActorRotation().Yaw, AimDirection.Rotation().Yaw);
		Turret->MoveToAzimuth(DesiredAzimuth);
	}
}