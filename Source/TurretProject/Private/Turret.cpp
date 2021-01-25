#include "Turret.h"
#include "Weapon.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;

	BasePart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BasePart"));
	RootComponent = BasePart;

	RotatingPartPivot = CreateDefaultSubobject<USceneComponent>(TEXT("RotatingPartPivot"));
	RotatingPartPivot->SetupAttachment(BasePart);
	RotatingPartPivot->SetRelativeLocation(FVector(0, 0, 100));

	RotatingPart = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RotatingPart"));
	RotatingPart->SetupAttachment(RotatingPartPivot);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(BasePart);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->SocketOffset = FVector(0, 0, 150);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	if (WeaponClass)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Weapon = GetWorld()->SpawnActor<AWeapon>(WeaponClass, SpawnInfo);
		Weapon->SetActorLocation(RotatingPart->GetComponentLocation());
	}
}

void ATurret::Tick(float DeltaTime)
{
	auto rot = GetViewRotation();
	RotatingPart->SetWorldRotation(FRotator(0, rot.Yaw, 0));

	if (Weapon)
	{
		Weapon->SetActorRotation(FRotator(rot.Pitch, rot.Yaw, 0));
	}

	Super::Tick(DeltaTime);
}

void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATurret::OnStartFiring);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATurret::OnStopFiring);
}

void ATurret::OnStartFiring()
{
	if (Weapon)
	{
		Weapon->OnStartFiring();
	}
}

void ATurret::OnStopFiring()
{
	if (Weapon)
	{
		Weapon->OnStopFiring();
	}
}