#include "AS/EnemyAttributeSet.h"

#include "GameplayEffectExtension.h"

UEnemyAttributeSet::UEnemyAttributeSet()
{
	InitMaxHealth(100.f);
	InitHealth(100.f);
}

void UEnemyAttributeSet::PreAttributeChange(const FGameplayAttribute & Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
}

void UEnemyAttributeSet::PostAttributeChange(const FGameplayAttribute & Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute())
	{
		if (OldValue < NewValue)
		{
			SetHealth(GetHealth() + (NewValue - OldValue));
		}
		else
		{
			SetHealth(FMath::Min(GetHealth(), NewValue));
		}
	}
}

void UEnemyAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));

		if (GetHealth() <= 0.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Enemy has died."));
		}
	}
}
