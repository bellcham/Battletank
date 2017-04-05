// Fill out your copyright notice in the Description page of Project Settings.

#include "Battletank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	if (GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController %s is controlling %s"), *this->GetName(), *GetControlledTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController %s is not controlling a tank"), *(this->GetName()));
	}
	if (GetPlayerTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController %s detected player tank %s"), *(this->GetName()), *GetPlayerTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController %s did not detect a player tank"), *(this->GetName()));
	}
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}


