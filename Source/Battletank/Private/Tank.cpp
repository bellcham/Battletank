// Adam Bellchambers 2017

#include "Battletank.h"
#include "Tank.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}


float ATank::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	float DamageToApply = 0.f;
	if ((ActualDamage > 0.f) && (Health > 0))
	{
		DamageToApply = FMath::Clamp<float>(ActualDamage, 0.f, Health);
		Health -= DamageToApply;
		UE_LOG(LogTemp, Warning, TEXT("%s incurred %f damage. Applied %f. Remaining health is %f"), *GetName(), ActualDamage,DamageToApply, Health);
		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (Health == 0.f)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s is dead!"), *GetName());
		}
	}

	return DamageToApply;
}
