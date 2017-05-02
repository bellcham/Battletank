// Adam Bellchambers 2017

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetThrottle(float Throttle);
	
	// Max force, per track, in newtons.
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxTractiveForce = 200000;

private:
	UTankTrack();
	virtual void BeginPlay() override;
	
	UFUNCTION(Category = "Events")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	void ApplySidewaysForce();
	float CurrentThrottle = 0.0f;
	void DriveTrack();
};
