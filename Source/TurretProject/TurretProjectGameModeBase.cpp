#include "TurretProjectGameModeBase.h"
#include "Public/TurretPlayerController.h"
#include "Public/TurretProjectDeveloperSettings.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "Public/Enemy.h"

ATurretProjectGameModeBase::ATurretProjectGameModeBase()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 1;

	PlayerControllerClass = ATurretPlayerController::StaticClass();

}

void ATurretProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* Actor = *It;
		if (Actor->ActorHasTag("EnemySpawn"))
		{
			spawnPointActor = Actor;
			break;
		}
	}
}

void ATurretProjectGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!spawnPointActor)
		return;

	if (Lives == 0)
	{
		auto controller = Cast<ATurretPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (controller && controller->GetPawn())
			controller->UnPossess();
	}

	auto settings = GetMutableDefault<UTurretProjectDeveloperSettings>();

	if (settings->EnemyClass)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		auto Enemy = GetWorld()->SpawnActor<AEnemy>(settings->EnemyClass, SpawnInfo);
		Enemy->SetActorLocation(spawnPointActor->GetActorLocation());
	}
}