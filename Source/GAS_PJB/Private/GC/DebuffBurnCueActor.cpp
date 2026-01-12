#include "GC/DebuffBurnCueActor.h"

#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ADebuffBurnCueActor::ADebuffBurnCueActor()
{
	GameplayCueTag = FGameplayTag::RequestGameplayTag(FName("GameplayCue.Debuff.Burn"));
	bAutoDestroyOnRemove = true;
}

bool ADebuffBurnCueActor::OnActive_Implementation(AActor * MyTarget, const FGameplayCueParameters & Parameters)
{
	if (SpawnedVFX.IsValid())
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}

	if (MyTarget)
	{
		SpawnedVFX = UNiagaraFunctionLibrary::SpawnSystemAtLocation(
			GetWorld(),
			FountainVFX,
			MyTarget->GetActorLocation(),
			MyTarget->GetActorRotation()
		);
		return true;
	}
	return false;
}

bool ADebuffBurnCueActor::OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters)
{
	if (SpawnedVFX.IsValid())
	{
		SpawnedVFX->Deactivate();
		SpawnedVFX = nullptr;
	}
	return true;
}
