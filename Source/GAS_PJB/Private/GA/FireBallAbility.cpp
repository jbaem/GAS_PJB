#include "GA/FireBallAbility.h"

#include "Projectile/FireBallProjectile.h"

UFireBallAbility::UFireBallAbility()
{}

void UFireBallAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if(!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
		return;
	}

	AActor* Spawner = ActorInfo->AvatarActor.Get();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = Cast<APawn>(Spawner);
	SpawnParams.Owner = Spawner;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = Spawner->GetActorLocation() + Spawner->GetActorForwardVector() * 300.f;
	FRotator SpawnRotation = Spawner->GetActorRotation();
	
	GetWorld()->SpawnActor<AActor>(
		FireBallClass, 
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	EndAbility(Handle, ActorInfo, ActivationInfo, true, false);
}
