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

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (Ammunition == 0)
	{
		AimingState = EAimingState::NoAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		AimingState = EAimingState::Reloading;
	}
	else if (bIsBarrelAimed)
	{
		AimingState = EAimingState::Locked;
	}
	else
	{
		AimingState = EAimingState::Aiming;
	}
}

void UTankAimingComponent::AimAt(FVector TargetLocation)
{
	if (!ensure(Barrel && Turret)) { return; }
	FVector SuggestedVelocity;
	bIsBarrelAimed = false;
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
		bIsBarrelAimed = AimDirection.Equals(Barrel->GetForwardVector().GetSafeNormal(), 0.01f);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && ProjectileBlueprint)) { return; }
	if (Ammunition <= 0) { return;  }
	if (AimingState != EAimingState::Reloading)
	{
		// Spawn a projectile at the socket location on the barrel.
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		Projectile->Launch(FiringSpeed);
		LastFireTime = FPlatformTime::Seconds();
		Ammunition--;
	}
}

EAimingState UTankAimingComponent::GetAimingState()
{
	return AimingState;
}

uint8 UTankAimingComponent::GetAmmunition()
{
	return Ammunition;
}