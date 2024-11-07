// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// If in range, rotate turret towards tank.

	if (InFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	UE_LOG(LogTemp, Warning, TEXT("ATower::HandleDestruction"));
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimeHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (Tank == nullptr)
	{
		return;
	}

	if (InFireRange() && Tank->bAlive)
	{
		Super::Fire();
	}
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		// Find distance to tank
		const float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		// Check to see if tank is in range
		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}
