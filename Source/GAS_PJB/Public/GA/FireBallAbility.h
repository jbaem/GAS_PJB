#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "FireBallAbility.generated.h"

UCLASS()
class GAS_PJB_API UFireBallAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFireBallAbility();

	virtual void ActivateAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData
	) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main|Projectile")
	TSubclassOf<class AFireBallProjectile> FireBallClass;

};
