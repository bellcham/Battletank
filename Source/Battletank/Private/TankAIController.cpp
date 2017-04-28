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
	if (ensure(TargetTank))
	{
		auto PathFollowingResult = MoveToActor(TargetTank, AcceptanceRadius);
		TargetPosition = TargetTank->GetActorLocation();
		AimingComponent->AimAt(TargetPosition);
		//AimingComponent->Fire(); // TODO re-enable firing
	}
}



