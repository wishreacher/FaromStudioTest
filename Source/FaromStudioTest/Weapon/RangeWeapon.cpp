// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromStudioTest/Weapon/RangeWeapon.h"
#include "Components/WeaponBarrelComponent.h"
#include "FaromStudioTest/FaromStudioTestCharacter.h"

ARangeWeapon::ARangeWeapon()
{
	WeaponBarrel = CreateDefaultSubobject<UWeaponBarrelComponent>(TEXT("WeaponBarrelComponent"));
	WeaponBarrel->SetupAttachment(WeaponMesh, FName("MuzzleSocket"));
}

void ARangeWeapon::BeginPlay()
{
	Super::BeginPlay();
	SetAmmo(MaxAmmo);
}

void ARangeWeapon::StartFire()
{
	GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
	GetWorld()->GetTimerManager().SetTimer(ShotTimer, this, &ARangeWeapon::MakeShot, GetShotTimerInterval(), true);
	MakeShot();
}

void ARangeWeapon::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(ShotTimer);
}

void ARangeWeapon::MakeShot()
{
	AFaromStudioTestCharacter* CharacterOwner = GetCharacterOwner();
	
	if(!IsValid(CharacterOwner))
	{
		return;
	}

	if(!CanShoot())
	{
		StopFire();
		return;
	}

	APlayerController* Controller = CharacterOwner->GetController<APlayerController>();
	if(!IsValid(Controller))
	{
		return;
	}
	
	FVector PlayerViewPoint;
	FRotator PlayerViewRotation;
	Controller->GetPlayerViewPoint(PlayerViewPoint, PlayerViewRotation);
	FVector ViewDirection = PlayerViewRotation.RotateVector(FVector::ForwardVector);

	SetAmmo(Ammo - 1);
	WeaponBarrel->Shot(WeaponBarrel->GetComponentLocation(), ViewDirection);
}

void ARangeWeapon::SetAmmo(int32 NewAmmo)
{
	Ammo = NewAmmo;
}

bool ARangeWeapon::CanShoot() const
{
	return Ammo > 0;
}

int32 ARangeWeapon::GetAmmo() const
{
	return Ammo;
}

int32 ARangeWeapon::GetAvailableAmmo() const
{
	return AvailableAmmo;
}

void ARangeWeapon::StartReload()
{
	if(Ammo == MaxAmmo)
	{
		return;
	}
	AFaromStudioTestCharacter* CharacterOwner = GetCharacterOwner();
	if(!IsValid(CharacterOwner))
	{
		return;
	}
	
	
	int32 AmmoToReload = MaxAmmo - Ammo;
	int32 ReloadedAmmo = FMath::Min(AvailableAmmo, AmmoToReload);

	AvailableAmmo -= ReloadedAmmo;
	SetAmmo(ReloadedAmmo + Ammo);
}

float ARangeWeapon::GetShotTimerInterval()
{
	return 60.f / RateOfFire;
}
