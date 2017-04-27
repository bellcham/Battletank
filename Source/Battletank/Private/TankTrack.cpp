// Adam Bellchambers 2017

#include "Battletank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) 
{
	// TODO Clamp throttle values to reasonable values
	auto ForceApplied = GetForwardVector() * Throttle * TrackMaxTractiveForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}
