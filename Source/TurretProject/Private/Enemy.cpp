#include "Enemy.h"
#include "../TurretProjectGameModeBase.h"
#include "EngineUtils.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"

AEnemy::AEnemy()
{
	this->AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->ActorHasTag("EnemyGoal"))
		{
			auto aicontroller = Cast<AAIController>(GetController());
			if (aicontroller)
			{
				aicontroller->MoveToActor(Actor, 400);
				aicontroller->ReceiveMoveCompleted.AddDynamic(this, &AEnemy::OnMoveCompleted);
				break;
			}
		}
	}
}

void AEnemy::GetDamaged(float amount)
{
	if (Health > 0)
	{
		Health -= amount;
		if (Health <= 0)
		{
			auto gamemode = Cast<ATurretProjectGameModeBase>(UGameplayStatics::GetGameMode(this));
			if (gamemode)
				gamemode->Score += 1;
			Destroy();
		}
	}
}

void AEnemy::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	auto gamemode = Cast<ATurretProjectGameModeBase>(UGameplayStatics::GetGameMode(this));
	if (gamemode)
		gamemode->Lives -= 1;
	Destroy();
}