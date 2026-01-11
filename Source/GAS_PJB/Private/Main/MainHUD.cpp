#include "Main/MainHUD.h"

#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Player/MainCharacter.h"
#include "UI/MainWidget.h"
#include "UI/BarWidget.h"
#include "Interface/ResourceBar.h"

AMainHUD::AMainHUD()
{}

void AMainHUD::BeginPlay()
{
	if (MainWidgetClass)
	{
		MainWidgetInstance = CreateWidget<UUserWidget>(GetOwningPlayerController(), MainWidgetClass);
		if (MainWidgetInstance)
		{
			MainWidgetInstance->AddToViewport();
		}
	}
}
