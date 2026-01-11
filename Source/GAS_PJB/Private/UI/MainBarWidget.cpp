#include "UI/MainBarWidget.h"

#include "Player/MainCharacter.h"

void UMainBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(APawn* Pawn = GetOwningPlayerPawn())
	{
		if(AMainCharacter* MainCharacter = Cast<AMainCharacter>(Pawn))
		{
			MainCharacter->OnManaChangedDelegate.AddDynamic(this, &UMainBarWidget::UpdateByBinded);
		}
	}
}

void UMainBarWidget::NativeDestruct()
{
	if (APawn* Pawn = GetOwningPlayerPawn())
	{
		if (AMainCharacter* MainCharacter = Cast<AMainCharacter>(Pawn))
		{
			MainCharacter->OnManaChangedDelegate.RemoveDynamic(this, &UMainBarWidget::UpdateByBinded);
		}
	}

	Super::NativeDestruct();
}

void UMainBarWidget::UpdateByBinded(float NewCurrent, float NewMax)
{
	UpdateAll_Implementation(NewCurrent, NewMax);
}
