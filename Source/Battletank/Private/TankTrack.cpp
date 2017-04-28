// Adam Bellchambers 2017

#include "Battletank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Calculate the slippage speed
	auto SidewaysSpeed = FVector::DotProduct(GetOwner()->GetVelocity(), GetOwner()->GetActorRightVector().GetSafeNormal());
	DrawDebugLine(
		GetWorld(), 
		GetOwner()->GetActorLocation() + FVector(0, 0, 200), 
		GetOwner()->GetActorLocation() + (SidewaysSpeed * GetOwner()->GetActorRightVector().GetSafeNormal()) + FVector(0, 0, 200), 
		FColor(255, 0, 0, 0), 
		true
	);
	// work out the required acceleration this frame to correct
	float RequiredAcceleration = SidewaysSpeed / DeltaTime;
	// Calculate required force
	float RequiredForce = GetOwner()->

void UTankTrack::SetThrottle(float Throttle) 
{
	// TODO Clamp throttle values to reasonable values
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxTractiveForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
