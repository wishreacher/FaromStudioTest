// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromStudioTest/Weapon/Components/WeaponBarrelComponent.h"
#include "NiagaraComponent.h"
#include "FaromStudioTest/FaromStudioTestCharacter.h"
#include "Kismet/GameplayStatics.h"

bool UWeaponBarrelComponent::HitScan(FVector ShotStart, FVector ShotDirection,
                                     OUT FVector& ShotEnd, FHitResult ShotResult) 
{
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	AFaromStudioTestCharacter* PlayerCharacter = Cast<AFaromStudioTestCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	// if(IsValid(PlayerCharacter))
	// {
		QueryParams.AddIgnoredActor(GetOwner());
	// }
	
	bool bHasHit = GetWorld()->LineTraceSingleByChannel(ShotResult, ShotStart, ShotEnd, ECC_Bullet, QueryParams);
	if(bHasHit)
	{
		ProcessHit(ShotResult, ShotDirection);
	}
	return bHasHit;
}

void UWeaponBarrelComponent::ProcessHit(const FHitResult& Hit, const FVector& Direction)
{
	AActor* HitActor = Hit.GetActor();

	FPointDamageEvent DamageEvent;
	DamageEvent.HitInfo = Hit;
	DamageEvent.ShotDirection = Direction;
	DamageEvent.DamageTypeClass = DamageTypeClass;
	HitActor->TakeDamage(BaseDamageAmount, DamageEvent, GetController(), GetOwner());
}

void UWeaponBarrelComponent::Shot(FVector ShotStart, FVector ShotDirection)
{
	FHitResult ShotResult;
	FVector MuzzleLocation = GetComponentLocation();
	
	FVector ShotEnd = ShotStart + FireRange * ShotDirection;
	
	DrawDebugSphere(GetWorld(), ShotEnd, 10.0f, 24, FColor::Red, false, 1.0f);
	DrawDebugLine(GetWorld(), MuzzleLocation, ShotEnd, FColor::Red, false, 1.0f, 0, 3.0f);
}

APawn* UWeaponBarrelComponent::GetOwningPawn() const
{
	APawn* PawnOwner = Cast<APawn>(GetOwner());
	if(!IsValid(PawnOwner))
	{
		PawnOwner = Cast<APawn>(GetOwner()->GetOwner());
	}
	return PawnOwner;
}

AController* UWeaponBarrelComponent::GetController() const
{
	APawn* PawnOwner = GetOwningPawn();
	if(IsValid(PawnOwner))
	{
		return PawnOwner->GetController();
	}
	return nullptr;
}

