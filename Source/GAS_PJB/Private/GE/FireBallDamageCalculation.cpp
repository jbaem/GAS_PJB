#include "GE/FireBallDamageCalculation.h"

#include "AS/EnemyAttributeSet.h"
#include "AbilitySystemComponent.h"

struct FFireDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Health);

	FFireDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UEnemyAttributeSet, Health, Target, false);
	}
};

static FFireDamageStatics& FireDamageStatics()
{
	static FFireDamageStatics Statics;
	return Statics;
}

UFireBallDamageCalculation::UFireBallDamageCalculation()
{
	RelevantAttributesToCapture.Add(FireDamageStatics().HealthDef);

	Tag_DebuffBurn = FGameplayTag::RequestGameplayTag(FName("State.Debuff.Burn"));
	Tag_ElementFire = FGameplayTag::RequestGameplayTag(FName("Element.Fire"));
}

void UFireBallDamageCalculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters & ExecutionParams, OUT FGameplayEffectCustomExecutionOutput & OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	if (TargetASC)
	{
		const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

		const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
		float Damage = BaseDamage;
		float Multiplier = DamageMultiplier;

		if (TargetTags && TargetTags->HasTag(Tag_DebuffBurn))
		{
			Damage *= Multiplier;
			UE_LOG(LogTemp, Warning, TEXT("Burn Tag Detected! Double Damage: %f"), Damage);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("No Burn Tag. Normal Damage: %f"), Damage);
		}
		if(Damage > 0.f)
		{
			OutExecutionOutput.AddOutputModifier(
				FGameplayModifierEvaluatedData(
					FireDamageStatics().HealthProperty, 
					EGameplayModOp::Additive, 
					-Damage
				)
			);
		}
	}
}
