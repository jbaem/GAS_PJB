#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/ResourceBar.h"

#include "BarWidget.generated.h"

UCLASS()
class GAS_PJB_API UBarWidget : public UUserWidget, public IResourceBar
{
	GENERATED_BODY()

public:
	virtual void UpdateCurrent_Implementation(float Value) override;
	virtual void UpdateMax_Implementation(float Value) override;
	virtual void UpdateAll_Implementation(float NewCurrent, float NewMax) override;

	UFUNCTION(BlueprintCallable, Category = "Main|UI")
	void SetProgressBarColor(FLinearColor NewColor);

private:
	inline float ValuesToPercent();

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UProgressBar> ProgressBar = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Current = nullptr;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<class UTextBlock> Max = nullptr;
	
private:
	float CurrentValue = 0.f;
	float MaxValue = 1.f;
};
