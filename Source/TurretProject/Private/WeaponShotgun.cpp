#include "WeaponShotgun.h"

void AWeaponShotgun::OnStartFiring()
{
	if (ProjectileClass != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = MuzzleLocation->GetComponentRotation();
			const FVector SpawnLocation = MuzzleLocation->GetComponentLocation();

			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			for (int i = 0; i < 13; ++i)
			{
				float max = 15;
				const float pitch = FMath::FRandRange(-max, max);
				const float yaw = FMath::FRandRange(-max, max);
				const float roll = FMath::FRandRange(-max, max);
				FRotator bla = FRotator(pitch, yaw, roll);
				FRotator random = bla + SpawnRotation;
				World->SpawnActor<AActor>(ProjectileClass, SpawnLocation, random, ActorSpawnParams);
			}
		}
	}
}

void AWeaponShotgun::OnStopFiring()
{

}