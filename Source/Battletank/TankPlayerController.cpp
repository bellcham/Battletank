// Adam Bellchambers 2017

#include "Battletank.h"
#include "TankAimingComponent.h"
#include "../Public/Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (ensure(ControlledTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController %s is controlling %s"), *(this->GetName()), *GetControlledTank()->GetName());
		auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController %s is not controlling a tank"), *(this->GetName()));
	}
	
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!ensure(GetControlledTank())) { return;  }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		//DrawDebugLine(GetWorld(), HitLocation, HitLocation + FVector(0.f, 0.f, 10000.f), FColor(255, 0, 0, 0), false);
		//if it hits the landscape, tell controlled tank to aim at this point
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &HitLocation) const
{
	//Get world location of linetrace through crosshair
	int32 ViewportSizeX, ViewportSizeY;
		GetViewportSize(ViewportSizeX, ViewportSizeY);
	
	int32 CrosshairPixelsX, CrosshairPixelsY;
	// HACK hard coded pixel ratios
	CrosshairPixelsX = ViewportSizeX * 0.5f;
	CrosshairPixelsY = ViewportSizeY * 0.33f;
	
	FVector CrosshairWorldOrigin, CrosshairWorldDirection;
	DeprojectScreenPositionToWorld(CrosshairPixelsX, CrosshairPixelsY, CrosshairWorldOrigin, CrosshairWorldDirection);
	
	// Line trace from crosshair origin along crosshair direction looking for terrain
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(
		OUT Hit,
		CrosshairWorldOrigin,
		CrosshairWorldOrigin + (CrosshairWorldDirection * 1000000), // HACK hard coded max trace range
		ECollisionChannel::ECC_Camera,
		FCollisionQueryParams(FName(TEXT("")), false, GetOwner())
	)) {
		HitLocation = Hit.ImpactPoint;
		return true;
	}
	// TODO if we are aiming at the skybox, no hit will be returned. do we need to aim using camera azimuth and elevation in that case?
	return false;
}
