// Fill out your copyright notice in the Description page of Project Settings.

#include "Battletank.h"
#include "../Public/TankBarrel.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::AimAt(FVector TargetLocation, float FiringSpeed)
{
	if (!Barrel) { return; }
	auto TankName = GetOwner()->GetName();
	FVector SuggestedVelocity;
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		GetWorld(),
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
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}