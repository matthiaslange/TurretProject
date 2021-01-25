#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TurretProjectDeveloperSettings.generated.h"

class AEnemy;

UCLASS(BlueprintType, config = Game, defaultconfig)
class TURRETPROJECT_API UTurretProjectDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:
	UPROPERTY(config, EditAnywhere, BlueprintReadWrite, Category = ProjectConfig)
	TSubclassOf<AEnemy> EnemyClass;
};
