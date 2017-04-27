// Adam Bellchambers 2017

#pragma once

#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	void Launch(float LaunchSpeed);

protected:
	virtual void BeginPlay() override;

private:
	UProjectileMovementComponent* MovementComponent = nullptr;
};
