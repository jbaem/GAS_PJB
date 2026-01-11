#include "AS/PlayerAttributeSet.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitMaxMana(100.f);
	InitMana(100.f);
}

void UPlayerAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	if(Attribute == GetMaxManaAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.f);
	}

	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UPlayerAttributeSet::PostAttributeChange(const FGameplayAttribute & Attribute, float OldValue, float NewValue)
{
	if (Attribute == GetMaxManaAttribute())
	{
		if (OldValue < NewValue)
		{
			SetMana(GetMana() + (NewValue - OldValue));
		}
		else
		{
			SetMana(FMath::Min(GetMana(), NewValue));
		}
	}
}

void UPlayerAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData & Data)
{}
