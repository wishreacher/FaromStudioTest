// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromStudioTest/Weapon/RangeWeapon.h"
#include "Components/WeaponBarrelComponent.h"
#include "FaromStudioTest/FaromStudioTestCharacter.h"

ARangeWeapon::ARangeWeapon()
{
	WeaponBarrel = CreateDefaultSubobject<UWeaponBarrelComponent>(TEXT("WeaponBarrelComponent"));
	WeaponBarrel->SetupAttachment(RootComponent);
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
	
	if(bIsReloading)
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
	WeaponBarrel->Shot(PlayerViewPoint, ViewDirection);

	if(Ammo == 0)
	{
		CharacterOwner->Reload();
	}
}

void ARangeWeapon::SetAmmo(int32 NewAmmo)
{
	Ammo = NewAmmo;
	if(OnAmmoChanged.IsBound())
	{
		OnAmmoChanged.Broadcast(Ammo);
	}
}

bool ARangeWeapon::CanShoot() const
{
	return Ammo > 0;
}

int32 ARangeWeapon::GetAmmo() const
{
	return Ammo;
}

int32 ARangeWeapon::GetMaxAmmo() const
{
	return MaxAmmo;
}

void ARangeWeapon::StartReload()
{
	if(Ammo == MaxAmmo)
	{
		return;
	}
	if(bIsReloading)
	{
		return;
	}
	AFaromStudioTestCharacter* CharacterOwner = GetCharacterOwner();
	if(!IsValid(CharacterOwner))
	{
		return;
	}
	
	bIsReloading = true;
	EndReload(true);
	
}

void ARangeWeapon::EndReload(bool bIsSuccess)
{
	if(!bIsReloading)
	{
		return;
	}

	bIsReloading = false;

	if(OnReloadBegin.IsBound())
	{
		OnReloadBegin.Broadcast();
	}
	
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);
	if(bIsSuccess && OnReloadComplete.IsBound())
	{
		OnReloadComplete.Broadcast();
	}
}

bool ARangeWeapon::GetIsReloading() const
{
	if(this)
	{
		return bIsReloading;
	}
	return false;
}

float ARangeWeapon::GetShotTimerInterval()
{
	return 60.f / RateOfFire;
}
