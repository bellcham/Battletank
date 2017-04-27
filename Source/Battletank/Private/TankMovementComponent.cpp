// Adam Bellchambers 2017

#include "Battletank.h"
#include "../Public/TankTrack.h"
#include "TankMovementComponent.h"


void UTankMovementComponent::Initialise(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	RightTrack = RightTrackToSet;
	LeftTrack = LeftTrackToSet;
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	IntendMoveForward(FVector::DotProduct(AIForwardIntention, TankForward));
	IntendMoveClockwise(FVector::CrossProduct(TankForward, AIForwardIntention).Z);
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendMoveClockwise(float Throw)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-1.f * Throw);
}