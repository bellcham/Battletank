// Adam Bellchambers 2017

#include "Battletank.h"
#include "Projectile.h"

AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Movement Component"));
	MovementComponent->bAutoActivate = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::Launch(float LaunchSpeed)
{
	if (!ensure(MovementComponent)) { return; }
	MovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * LaunchSpeed);
	MovementComponent->Activate();
}

