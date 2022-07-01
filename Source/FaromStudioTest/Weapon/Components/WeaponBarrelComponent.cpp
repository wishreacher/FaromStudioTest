// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromStudioTest/Weapon/Components/WeaponBarrelComponent.h"
#include "NiagaraComponent.h"
#include "FaromStudioTest/FaromStudioTestCharacter.h"
#include "Kismet/GameplayStatics.h"

bool UWeaponBarrelComponent::HitScan(FVector ShotStart, FVector ShotDirection,
                                     OUT FVector& ShotEnd, FHitResult ShotResult) 
{
	FCollisionQueryParams QueryParams = FCollisionQueryParams::DefaultQueryParam;
	QueryParams.AddIgnoredActor(GetOwner());
	QueryParams.AddIgnoredActor(GetOwningPawn());
	
	bool bHasHit = GetWorld()->LineTraceSingleByChannel(ShotResult, ShotStart, ShotEnd, ECC_GameTraceChannel1, QueryParams);
	DrawDebugLine(GetWorld(), ShotStart, ShotEnd, FColor::Red, false, 1.0f, 0, 3.0f);
	if(bHasHit)
	{
		ProcessHit(ShotResult, ShotDirection);
	}
	return bHasHit;
}

void UWeaponBarrelComponent::ProcessHit(const FHitResult& Hit, const FVector& Direction)
{
	DrawDebugSphere(GetWorld(), Hit.Location, 10.0f, 24, FColor::Red, false, 1.0f);
	if(IsValid(HitSound))
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, Hit.Location);
	}
	
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
	FVector ShotEnd = ShotStart + FireRange * ShotDirection;
	bool bHasHit = HitScan(ShotStart, ShotDirection, ShotEnd, ShotResult);
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

