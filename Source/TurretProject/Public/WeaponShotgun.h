#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "WeaponShotgun.generated.h"

UCLASS()
class TURRETPROJECT_API AWeaponShotgun : public AWeapon
{
	GENERATED_BODY()
public:
	virtual void OnStartFiring() override;
	virtual void OnStopFiring() override;
};
