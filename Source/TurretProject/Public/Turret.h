#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Turret.generated.h"

class AWeapon;
class USpringArmComponent;
class UCameraComponent;

UCLASS(Blueprintable)
class TURRETPROJECT_API ATurret : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AWeapon> WeaponClass;

	AWeapon* Weapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* BasePart;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* RotatingPart;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RotatingPartPivot;


public:
	ATurret();

protected:
	virtual void BeginPlay() override;

	void OnStartFiring();
	void OnStopFiring();
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
