// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "RangeWeapon.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, int32)
DECLARE_MULTICAST_DELEGATE(FOnReloadBegin)
DECLARE_MULTICAST_DELEGATE(FOnReloadComplete)
/**
 * 
 */
UCLASS(Blueprintable)
class FAROMSTUDIOTEST_API ARangeWeapon : public ABaseWeapon
{
	GENERATED_BODY()

	ARangeWeapon();
public:
	void StartFire();
	void StopFire();
	void MakeShot();
	
	void SetAmmo(int32 NewAmmo);
	bool CanShoot() const;

	UFUNCTION(BlueprintCallable)
	int32 GetAmmo() const;

	UFUNCTION(BlueprintCallable)
	int32 GetMaxAmmo() const;

	void StartReload();
	void EndReload(bool bIsSuccess);
	FOnReloadComplete OnReloadComplete;
	FOnReloadBegin OnReloadBegin;
	bool GetIsReloading() const;
	FOnAmmoChanged OnAmmoChanged;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UWeaponBarrelComponent* WeaponBarrel;
	
	UPROPERTY(EditAnywhere, Category = "Weapon|Parameters", meta = (ClampMin = 10.f, UIMin = 10.f))
	float RateOfFire = 600.f;

	UPROPERTY(EditAnywhere, Category = "Weapon|Parameters|Aiming", meta = (ClampMin = 1, UIMin = 1))
	int32 MaxAmmo = 30;

private:
	int32 Ammo = 0;
	bool bCanShot = true;
	bool bIsReloading = false;

	FTimerHandle ShotTimer;
	FTimerHandle ReloadTimer;
	FTimerHandle CanShootTimer;

	float GetShotTimerInterval();
};
