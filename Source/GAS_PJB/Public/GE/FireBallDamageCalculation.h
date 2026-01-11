#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"

#include "FireBallDamageCalculation.generated.h"

UCLASS()
class GAS_PJB_API UFireBallDamageCalculation : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
	
public:
	UFireBallDamageCalculation();

	virtual void Execute_Implementation(
		const FGameplayEffectCustomExecutionParameters& ExecutionParams, 
		OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput
	) const override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Main|Damage")
	float BaseDamage = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Main|Damage")
	float DamageMultiplier = 2.f;
	
private:
	FGameplayTag Tag_DebuffBurn;
	FGameplayTag Tag_ElementFire;
};
