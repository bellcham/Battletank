// Adam Bellchambers 2017

#include "Battletank.h"
#include "../Public/TankMovementComponent.h"
#include "../Public/TankAimingComponent.h"
#include "../Public/TankBarrel.h"
#include "../Public/TankTurret.h"
#include "../Public/Projectile.h"
#include "../Public/Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::AimAt(FVector TargetLocation)
{
	if (!ensure(AimingComponent)) { return; }
	AimingComponent->AimAt(TargetLocation, FiringSpeed);
}

// TODO Delete
//void ATank::SetBarrelReference(UTankBarrel * BarrelToSet)
//{
//	AimingComponent->SetBarrelReference(BarrelToSet);
//	Barrel = BarrelToSet;
//}
//
//void ATank::SetTurretReference(UTankTurret * TurretToSet)
//{
//	AimingComponent->SetTurretReference(TurretToSet);
//}

void ATank::Fire()
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

