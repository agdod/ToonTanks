// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include <GameFramework/SpringArmComponent.h>
#include <Kismet/GameplayStatics.h>

#include "Projectile.h"
#include "Engine/LocalPlayer.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	CameraComponent->SetupAttachment(SpringArm);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput =
		CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Move
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::Move);
		// Rotate Turret
		EnhancedInput->BindAction(RotateTurretAction, ETriggerEvent::Triggered, this, &ATank::RotateTurret);
		// Fire Projectile
		EnhancedInput->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATank::Fire);
	}
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(
			ECollisionChannel::ECC_Visibility,
			false,
			HitResult);

		ABasePawn::RotateTurret(HitResult.ImpactPoint);
	}
}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();
	UE_LOG(LogTemp, Display, TEXT("ATank::HandleDestruction"));
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(TankMappingContext, 0);
		}
	}
}

void ATank::Move(const FInputActionValue& Value)
{
	const FVector2D MoveValue = Value.Get<FVector2D>();
	//const float DirectionValue = Value.Get<float>();

	if (Controller && (MoveValue != FVector2D::ZeroVector))
	{
		FVector DeltaLocation = FVector::ZeroVector;
		const float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
		// X = Value * DeltaTime * Speed

		DeltaLocation.X = MoveValue.X * DeltaTime * Speed;
		AddActorLocalOffset(DeltaLocation, true);

		FRotator DeltaRotation = FRotator::ZeroRotator;
		DeltaRotation.Yaw = MoveValue.Y * TurnRate * DeltaTime;
		AddActorLocalRotation(DeltaRotation, true);
	}
}

void ATank::RotateTurret(const FInputActionValue& Value)
{
	const float TurnValue = Value.Get<float>();
	if (Controller && (TurnValue != 0.f))
	{
	}
}

void ATank::Fire()
{
	Super::Fire();
}
