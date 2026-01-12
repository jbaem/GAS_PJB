#pragma once

#include "CoreMinimal.h"
#include "GameplayCueNotify_Actor.h"

#include "DebuffBurnCueActor.generated.h"

UCLASS()
class GAS_PJB_API ADebuffBurnCueActor : public AGameplayCueNotify_Actor
{
	GENERATED_BODY()

public:
	ADebuffBurnCueActor();

	virtual bool OnActive_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;
	virtual bool OnRemove_Implementation(AActor* MyTarget, const FGameplayCueParameters& Parameters) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MainVFX")
	TObjectPtr<class UNiagaraSystem> FountainVFX = nullptr;

private:
	UPROPERTY()
	TWeakObjectPtr<class UNiagaraComponent> SpawnedVFX = nullptr;
};
