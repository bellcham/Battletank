// Adam Bellchambers 2017

#include "Battletank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TargetTank = Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn());
	if (!ensure(TargetTank)) { return; }
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (ensure(TargetTank))
	{
		auto PathFollowingResult = MoveToActor(TargetTank, AcceptanceRadius);
		TargetPosition = TargetTank->GetActorLocation() + FVector(0.f,0.f,75.f); // Aim 0.75m above target tank location
		AimingComponent->AimAt(TargetPosition);
		if(AimingComponent->GetAimingState() == EAimingState::Locked)
		{
			AimingComponent->Fire(); 
		}
		
	}
}



