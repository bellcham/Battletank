// Adam Bellchambers 2017

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	ATank* ControlledTank = nullptr;
	ATank* TargetTank = nullptr;
	FVector TargetPosition;

	float AcceptanceRadius = 3000.f;
	
};
