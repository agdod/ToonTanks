// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "InputActionValue.h"
#include "Tank.generated.h"

class UInputAction;

UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void HandleDestruction() override;
	APlayerController* GetPlayerController() const { return PlayerController; }

	bool bAlive = true;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	class UInputMappingContext* TankMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* RotateTurretAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* FireAction;

private:
	UPROPERTY(VisibleAnywhere, Category = CustomComponents)
	class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleAnywhere, Category = CustomComponents)
	class UCameraComponent* CameraComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float Speed{250.f};
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float TurnRate{100.f};
	UPROPERTY(VisibleAnywhere, Category = "Components")
	APlayerController* PlayerController;

	void Move(const FInputActionValue& Value);
	void RotateTurret(const FInputActionValue& Value);
	virtual void Fire() override;
};
