#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "FireBallProjectile.generated.h"

UCLASS()
class GAS_PJB_API AFireBallProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AFireBallProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main")
	TObjectPtr<class USphereComponent> SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main|Effects")
	TObjectPtr<class UNiagaraComponent> FireBallVFX;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditAnywhere, Category = "Main|GAS")
	TSubclassOf<class UGameplayEffect> DamageEffectClass;
	UPROPERTY(EditAnywhere, Category = "Main|GAS")
	TSubclassOf<class UGameplayEffect> BurnDotEffectClass;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult
	);
};
