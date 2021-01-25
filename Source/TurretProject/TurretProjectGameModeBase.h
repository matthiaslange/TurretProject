#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TurretProjectGameModeBase.generated.h"

UCLASS()
class TURRETPROJECT_API ATurretProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AActor* spawnPointActor = nullptr;

protected:
	virtual void BeginPlay() override;

public:
	ATurretProjectGameModeBase();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite)
	float Score = 0;

	UPROPERTY(BlueprintReadWrite)
	int32 Lives = 20;
};
