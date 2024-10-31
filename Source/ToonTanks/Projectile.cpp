// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>("Projectile Mesh");
	RootComponent = ProjectileMesh;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement");
	ProjectileMovement->MaxSpeed = 1600.f;
	ProjectileMovement->InitialSpeed = 1600.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                        FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Display, TEXT("Projectile Hit"));
	UE_LOG(LogTemp, Display, TEXT("HitComp: %s"), *HitComp->GetName());
	UE_LOG(LogTemp, Display, TEXT("OtherActor: %s"), *OtherActor->GetName());
	UE_LOG(LogTemp, Display, TEXT("OtherComp: %s"), *OtherComp->GetName());
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
