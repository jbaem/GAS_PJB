#include "Projectile/FireBallProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraComponent.h"

AFireBallProjectile::AFireBallProjectile()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(15.f);
	SphereComponent->SetCollisionProfileName(TEXT("Projectile"));
	RootComponent = SphereComponent;
	
	FireBallVFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("FireBallVFX"));
	FireBallVFX->SetupAttachment(RootComponent);
	
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = SphereComponent;
	ProjectileMovement->InitialSpeed = 1000.f;
	ProjectileMovement->MaxSpeed = 1000.f;
	ProjectileMovement->ProjectileGravityScale = 0.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AFireBallProjectile::OnOverlap);
}

void AFireBallProjectile::BeginPlay()
{
	Super::BeginPlay();

	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
	}
}

void AFireBallProjectile::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor == GetInstigator())
	{
		return;
	}

	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (TargetASC)
	{
		FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
		ContextHandle.AddInstigator(GetInstigator(), this);
		ContextHandle.AddHitResult(SweepResult);

		if (DamageEffectClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Applying Damage Effect"));

			FGameplayEffectSpecHandle DamageEffectSpecHandle = TargetASC->MakeOutgoingSpec(
				DamageEffectClass, 
				1.f, 
				ContextHandle
			);
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}

		if (BurnDotEffectClass)
		{
			UE_LOG(LogTemp, Warning, TEXT("Applying Burn DoT Effect"));

			FGameplayEffectSpecHandle BurnDotEffectSpecHandle = TargetASC->MakeOutgoingSpec(
				BurnDotEffectClass, 
				1.f, 
				ContextHandle
			);
			TargetASC->ApplyGameplayEffectSpecToSelf(*BurnDotEffectSpecHandle.Data.Get());
		}
	}
	Destroy();
}


