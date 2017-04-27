// Adam Bellchambers 2017

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EAimingState : uint8
{
	Reloading,
	Aiming,
	Locked
};

//Forward declaration
class UTankBarrel; 
class UTankTurret;

// Holds parameters for aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector TargetLocation, float FiringSpeed);
	
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FiringSpeed = 100000; // TODO Determine sensible default

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAimingState AimingState = EAimingState::Aiming;

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
};
