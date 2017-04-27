// Adam Bellchambers 2017

#pragma once


#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	ATank* GetControlledTank() const;
protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);
private:
	void AimTowardCrosshair();
	bool GetSightRayHitLocation(FVector &HitLocation) const;
};
