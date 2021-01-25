#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AITypes.h"
#include "Navigation/PathFollowingComponent.h"
#include "Enemy.generated.h"

UCLASS(Blueprintable)
class TURRETPROJECT_API AEnemy : public ACharacter
{
	GENERATED_BODY()

	UFUNCTION()
	void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result);

public:
	AEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100;

protected:
	virtual void BeginPlay() override;

public:	
	void GetDamaged(float amount);
};
