// Adam Bellchambers 2017

#include "Battletank.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
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

void UTankAimingComponent::AimAt(FVector TargetLocation)
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

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded)
	{
		// Spawn a projectile at the socket location on the barrel.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->Launch(FiringSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}