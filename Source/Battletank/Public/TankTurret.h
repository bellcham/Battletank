// Adam Bellchambers 2017

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	void MoveToAzimuth(float DesiredAzimuth);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesPerSecond = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
		float MaxDegreesAzimuth = 80.f;
};
