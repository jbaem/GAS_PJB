#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "MainCharacter.generated.h"

UCLASS()
class GAS_PJB_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main|Camera")
	TObjectPtr<class USpringArmComponent> CameraBoom;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Main|Camera")
	TObjectPtr<class UCameraComponent> FollowCamera;
};
