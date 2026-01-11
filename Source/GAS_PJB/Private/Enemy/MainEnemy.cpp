#include "Enemy/MainEnemy.h"

#include "Components/WidgetComponent.h"
#include "Interface/ResourceBar.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AS/EnemyAttributeSet.h"

AMainEnemy::AMainEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	BarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("BarWidget"));
	BarWidget->SetupAttachment(RootComponent);

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	EnemyAttributeSet = CreateDefaultSubobject<UEnemyAttributeSet>(TEXT("EnemyAttributeSet"));
}

void AMainEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}

	FOnGameplayAttributeValueChange& OnHealthChange =
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetHealthAttribute());
	OnHealthChange.AddUObject(this, &AMainEnemy::OnHealthChanged);

	FOnGameplayAttributeValueChange& OnMaxHealthChange =
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(UEnemyAttributeSet::GetMaxHealthAttribute());
	OnMaxHealthChange.AddUObject(this, &AMainEnemy::OnMaxHealthChanged);

	if (EnemyAttributeSet)
	{
		if (BarWidget && BarWidget->GetWidget())
		{
			IResourceBar::Execute_UpdateAll(BarWidget->GetWidget(), EnemyAttributeSet->GetHealth(), EnemyAttributeSet->GetMaxHealth());
		}
	}

}

void AMainEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMainEnemy::OnMaxHealthChanged(const FOnAttributeChangeData& Data)
{
	IResourceBar::Execute_UpdateMax(BarWidget->GetWidget(), EnemyAttributeSet->GetMaxHealth());
}

void AMainEnemy::OnHealthChanged(const FOnAttributeChangeData & Data)
{
	IResourceBar::Execute_UpdateAll(BarWidget->GetWidget(), EnemyAttributeSet->GetHealth(), EnemyAttributeSet->GetMaxHealth());
}
