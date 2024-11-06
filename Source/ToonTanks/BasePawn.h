// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

using namespace UP;

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	virtual void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void RotateTurret(FVector LookAtTarget);
	virtual void Fire();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CustomComponents, meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CustomComponents, meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CustomComponents, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = CustomComponents, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystem* DeathParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class USoundBase* DeathSound;

public:
};
