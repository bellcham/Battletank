// Fill out your copyright notice in the Description page of Project Settings.

#include "Battletank.h"
#include "../Public/Tank.h"
#include "../Public/TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());
	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController %s is controlling %s"), *this->GetName(), *ControlledTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController %s is not controlling a tank"), *(this->GetName()));
	}
	TargetTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (TargetTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController %s detected player tank %s"), *(this->GetName()), *TargetTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController %s did not detect a player tank"), *(this->GetName()));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	if (TargetTank && ControlledTank)
	{
		TargetPosition = TargetTank->GetActorLocation();
		ControlledTank->AimAt(TargetPosition);
		ControlledTank->Fire(); // TODO don't fire every frame
	}
}



