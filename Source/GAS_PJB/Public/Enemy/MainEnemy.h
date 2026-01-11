#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"

#include "MainEnemy.generated.h"

UCLASS()
class GAS_PJB_API AMainEnemy : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMainEnemy();

protected:
	virtual void BeginPlay() override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	void OnMaxHealthChanged(const FOnAttributeChangeData& Data);
	void OnHealthChanged(const FOnAttributeChangeData& Data);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main")
	TObjectPtr<class UWidgetComponent> BarWidget = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main|GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main|GAS")
	TObjectPtr<class UEnemyAttributeSet> EnemyAttributeSet = nullptr;

};
