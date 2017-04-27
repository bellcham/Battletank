// Adam Bellchambers 2017

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void MoveToElevation(float DesiredElevation);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesElevation = 40.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinDegreesElevation = -1.f;

	
	
	
};
