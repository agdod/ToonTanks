// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 *
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = TowerStats, meta = (AllowPrivateAccess = "true"))
	float FireRange{300.f};
	bool InRange{false};
	class ATank* Tank;
	FTimerHandle FireRateTimeHandle;
	float FireRate{2.f};
	void CheckFireCondition();
	bool InFireRange();
};
