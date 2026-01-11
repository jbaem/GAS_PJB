#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "MainPlayerController.generated.h"

UCLASS()
class GAS_PJB_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainPlayerController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Main|Input")
	TObjectPtr<class UInputMappingContext> DefaultMappingContext;
};
