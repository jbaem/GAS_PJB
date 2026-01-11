#pragma once

#include "CoreMinimal.h"
#include "UI/BarWidget.h"

#include "MainBarWidget.generated.h"

UCLASS()
class GAS_PJB_API UMainBarWidget : public UBarWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void UpdateByBinded(float NewCurrent, float NewMax);
};
