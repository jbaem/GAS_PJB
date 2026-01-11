#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"

#include "MainHUD.generated.h"

UCLASS()
class GAS_PJB_API AMainHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainHUD();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category = "Main|UI")
	TSubclassOf<UUserWidget> MainWidgetClass;
	UPROPERTY()
	TObjectPtr<UUserWidget> MainWidgetInstance;

};
