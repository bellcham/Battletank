// Adam Bellchambers 2017

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EAimingState : uint8
{
	Reloading,
	Aiming,
	Locked,
	NoAmmo
};

//Forward declaration
class UTankBarrel; 
class UTankTurret;
class AProjectile;

// Holds parameters for aiming
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	void AimAt(FVector TargetLocation);
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();
		
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FiringSpeed = 100000; // TODO Determine sensible default
	
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf<AProjectile> ProjectileBlueprint;



	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.f; //TODO Magic number

	EAimingState GetAimingState();
	uint8 GetAmmunition();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EAimingState AimingState = EAimingState::Reloading;
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
	uint8 Ammunition = 5;
private:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	double LastFireTime = 0;
	bool bIsBarrelAimed = false;
};
