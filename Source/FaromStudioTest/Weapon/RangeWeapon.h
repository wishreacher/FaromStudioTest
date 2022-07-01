// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWeapon.h"
#include "RangeWeapon.generated.h"
/**
 * 
 */
UCLASS(Blueprintable)
class FAROMSTUDIOTEST_API ARangeWeapon : public ABaseWeapon
{
	GENERATED_BODY()

	ARangeWeapon();
public:
	virtual void BeginPlay() override;
	
	void StartFire();
	void StopFire();
	void MakeShot();
	
	void SetAmmo(int32 NewAmmo);
	bool CanShoot() const;

	UFUNCTION(BlueprintCallable)
	int32 GetAmmo() const;

	UFUNCTION(BlueprintCallable)
	int32 GetAvailableAmmo() const;

	void StartReload();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UWeaponBarrelComponent* WeaponBarrel;
	
	UPROPERTY(EditAnywhere, Category = "Weapon|Parameters", meta = (ClampMin = 10.f, UIMin = 10.f))
	float RateOfFire = 600.f;

	UPROPERTY(EditAnywhere, Category = "Weapon|Parameters|Aiming", meta = (ClampMin = 1, UIMin = 1))
	int32 MaxAmmo = 30;

	UPROPERTY(EditAnywhere, Category = "Weapon|Parameters|Aiming", meta = (ClampMin = 1, UIMin = 1))
	int32 AvailableAmmo = 120;

private:
	int32 Ammo = 0;
	bool bCanShot = true;

	FTimerHandle ShotTimer;
	FTimerHandle CanShootTimer;

	float GetShotTimerInterval();
};
