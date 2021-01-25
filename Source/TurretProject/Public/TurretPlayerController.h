#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TurretPlayerController.generated.h"

UCLASS()
class TURRETPROJECT_API ATurretPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	ATurretPlayerController(const FObjectInitializer& ObjectInitializer);

	virtual void SetupInputComponent() override;

	void SwitchTurret();
};
