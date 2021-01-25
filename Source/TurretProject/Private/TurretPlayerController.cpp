#include "TurretPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Turret.h"

ATurretPlayerController::ATurretPlayerController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bAutoManageActiveCameraTarget = true;
}

void ATurretPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATurretPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("SwitchTurret", IE_Pressed, this, &ATurretPlayerController::SwitchTurret);
}

void ATurretPlayerController::SwitchTurret()
{
	APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(this, 0);
	if (CameraManager)
	{
		FVector ProjDirection = CameraManager->GetActorForwardVector();

		const FVector StartTrace = CameraManager->GetCameraLocation();
		const FVector EndTrace = CameraManager->GetCameraLocation() + ProjDirection * 15000;
		FHitResult Impact;

		GetWorld()->LineTraceSingleByChannel(Impact, StartTrace, EndTrace, ECC_Pawn, FCollisionQueryParams(SCENE_QUERY_STAT(ProjClient), true, GetInstigator()));

		auto turret = Cast<ATurret>(Impact.GetActor());
		if (turret)
		{
			bAutoManageActiveCameraTarget = false;
			FViewTargetTransitionParams params;
			params.BlendTime = 0.5f;
			params.BlendFunction = VTBlend_Cubic;
			params.bLockOutgoing = true;
			CameraManager->SetViewTarget(turret, params);
			Possess(turret);
		}		
	}
	
}