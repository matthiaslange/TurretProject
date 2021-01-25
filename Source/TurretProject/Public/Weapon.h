#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS(Blueprintable)
class TURRETPROJECT_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	AWeapon();

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AActor> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	USceneComponent* MuzzleLocation;

public:
	virtual void OnStartFiring();
	virtual void OnStopFiring();
};
