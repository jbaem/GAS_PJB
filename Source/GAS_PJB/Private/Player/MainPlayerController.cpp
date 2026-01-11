#include "Player/MainPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

AMainPlayerController::AMainPlayerController()
{

}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if(IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}
