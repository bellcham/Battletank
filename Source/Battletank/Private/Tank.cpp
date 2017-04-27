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

