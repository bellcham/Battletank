// Fill out your copyright notice in the Description page of Project Settings.

#include "Battletank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController %s is controlling %s"), *(this->GetName()), *GetControlledTank()->GetName());
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
	if (!GetControlledTank()) { return;  }
	
	
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hitlocation: %s"), *HitLocation.ToString());
		DrawDebugLine(GetWorld(), HitLocation, HitLocation + FVector(0.f, 0.f, 10000.f), FColor(255, 0, 0, 0), false);
		//if it hits the landscape, tell controlled tank to aim at this point
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
