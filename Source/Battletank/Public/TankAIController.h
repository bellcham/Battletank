// Adam Bellchambers 2017

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
protected:
	UTankAimingComponent* AimingComponent = nullptr;
private:
	AActor* TargetTank = nullptr;
	FVector TargetPosition;
	float AcceptanceRadius = 3000.f;
};
