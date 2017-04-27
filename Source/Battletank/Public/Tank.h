// Adam Bellchambers 2017

#pragma once


#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;
class UTankAimingComponent;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	virtual void BeginPlay() override;

protected:
	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent* AimingComponent = nullptr;


public:	
	void AimAt(FVector TargetLocation);
	
	// TODO Delete
	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//void SetBarrelReference(UTankBarrel* BarrelToSet);

	//UFUNCTION(BlueprintCallable, Category = "Setup")
	//void SetTurretReference(UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FiringSpeed = 100000; // TODO Determine sensible default

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f; //TODO Magic number


private:
	UTankBarrel* Barrel = nullptr;
	double LastFireTime = 0;
};
