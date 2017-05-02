// Adam Bellchambers 2017

#include "Battletank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.0, 1.0);
}


void UTankTrack::DriveTrack() 
{
	auto ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxTractiveForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	CurrentThrottle = 0.0f;
}

//DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams( FComponentHitSignature, UPrimitiveComponent*, HitComponent, AActor*, OtherActor, UPrimitiveComponent*, OtherComp, FVector, NormalImpulse, const FHitResult&, Hit );
void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//UE_LOG(LogTemp, Warning, TEXT("TankTrack Hit Event"))
	DriveTrack();
	ApplySidewaysForce();
}

void UTankTrack::ApplySidewaysForce()
{
	// Calculate the slippage speed
	auto SidewaysSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());
	// work out the required acceleration this frame to correct
	auto RequiredAcceleration = -1.0 * SidewaysSpeed / GetWorld()->DeltaTimeSeconds * GetRightVector();
	// Calculate required force
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	auto RequiredForce = (TankRoot->GetMass() * RequiredAcceleration) / 2;
	TankRoot->AddForce(RequiredForce);
}
