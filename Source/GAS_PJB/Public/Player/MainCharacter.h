#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"

#include "MainCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnManaChangedDelegate, float, Current, float, Max);

UCLASS()
class GAS_PJB_API AMainCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }
	FOnManaChangedDelegate OnManaChangedDelegate;

public:
	UFUNCTION(BlueprintCallable, Category = "Main|Character")
	void DoMove(float Right, float Forward);
	UFUNCTION(BlueprintCallable, Category = "Main|Character")
	void DoLook(float Yaw, float Pitch);

protected:
	void OnMove(const struct FInputActionValue& Value);
	void OnLook(const struct FInputActionValue& Value);
	void OnAbility1Pressed();

	void OnMaxManaChanged(const FOnAttributeChangeData& Data);
	void OnManaChanged(const FOnAttributeChangeData& Data);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main|Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main|Camera")
	TObjectPtr<class UCameraComponent> FollowCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main|Input")
	TObjectPtr<class UInputAction> MoveAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main|Input")
	TObjectPtr<class UInputAction> LookAction = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main|Input")
	TObjectPtr<class UInputAction> Ability1Action = nullptr;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main|GAS")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main|GAS")
	TObjectPtr<class UPlayerAttributeSet> PlayerAttributeSet = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Main|GAS")
	TSubclassOf<class UGameplayAbility> FireBallClass;
};
