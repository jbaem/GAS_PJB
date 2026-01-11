#include "Player/MainCharacter.h"

#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AS/PlayerAttributeSet.h"
#include "GAS/GASEnums.h"

AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	PlayerAttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>(TEXT("PlayerAttributeSet"));
	
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);

		if (FireBallClass)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(FireBallClass, 1, static_cast<int32>(EAbilityInputID::FIREBALL), this));
		}
	}

	FOnGameplayAttributeValueChange& OnManaChange =
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetManaAttribute());
	OnManaChange.AddUObject(this, &AMainCharacter::OnManaChanged);

	FOnGameplayAttributeValueChange& OnMaxManaChange =
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UPlayerAttributeSet::GetMaxManaAttribute());
	OnMaxManaChange.AddUObject(this, &AMainCharacter::OnMaxManaChanged);

	if (PlayerAttributeSet)
	{
		OnManaChangedDelegate.Broadcast(PlayerAttributeSet->GetMana(), PlayerAttributeSet->GetMaxMana());
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacter::OnMove);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainCharacter::OnLook);
		
		EnhancedInputComponent->BindAction(Ability1Action, ETriggerEvent::Started, this, &AMainCharacter::OnAbility1Pressed);
	}
}

void AMainCharacter::DoMove(float Right, float Forward)
{
	if (!GetController())
	{
		return;
	}

	const FRotator Rotation = GetController()->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, Forward);
	AddMovementInput(RightDirection, Right);
}

void AMainCharacter::DoLook(float Yaw, float Pitch)
{
	if (!GetController())
	{
		return;
	}

	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);
}

void AMainCharacter::OnMove(const FInputActionValue & Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	DoMove(MovementVector.X, MovementVector.Y);
}

void AMainCharacter::OnLook(const FInputActionValue & Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void AMainCharacter::OnAbility1Pressed()
{
	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EAbilityInputID::FIREBALL));
	}
}

void AMainCharacter::OnMaxManaChanged(const FOnAttributeChangeData& Data)
{
	OnManaChangedDelegate.Broadcast(PlayerAttributeSet->GetMana(), PlayerAttributeSet->GetMaxMana());
}

void AMainCharacter::OnManaChanged(const FOnAttributeChangeData & Data)
{
	OnManaChangedDelegate.Broadcast(PlayerAttributeSet->GetMana(), PlayerAttributeSet->GetMaxMana());
}

