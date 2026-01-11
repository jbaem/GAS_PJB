#include "UI/BarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBarWidget::UpdateCurrent_Implementation(float Value)
{
	Current->SetText(FText::AsNumber(FMath::RoundToInt(Value)));
	CurrentValue = Value;
	ProgressBar->SetPercent(ValuesToPercent());
}

void UBarWidget::UpdateMax_Implementation(float Value)
{
	Max->SetText(FText::AsNumber(FMath::RoundToInt(Value)));
	MaxValue = Value;
	ProgressBar->SetPercent(ValuesToPercent());
}

void UBarWidget::UpdateAll_Implementation(float NewCurrent, float NewMax)
{
	Current->SetText(FText::AsNumber(FMath::RoundToInt(NewCurrent)));
	CurrentValue = NewCurrent;
	Max->SetText(FText::AsNumber(FMath::RoundToInt(NewMax)));
	MaxValue = NewMax;
	ProgressBar->SetPercent(ValuesToPercent());
}

void UBarWidget::SetProgressBarColor(FLinearColor NewColor)
{
	ProgressBar->SetFillColorAndOpacity(NewColor);
}

inline float UBarWidget::ValuesToPercent()
{
	return MaxValue > 0.f ? CurrentValue / MaxValue : 0.f;
}
