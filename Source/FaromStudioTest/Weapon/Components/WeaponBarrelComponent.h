// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "WeaponBarrelComponent.generated.h"


class UNiagaraSystem;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FAROMSTUDIOTEST_API UWeaponBarrelComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	void Shot(FVector ShotStart, FVector ShotDirection);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel Attributes")
	float FireRange = 5000.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel Attributes")
	float BaseDamageAmount = 20.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel Attributes")
	TSubclassOf<UDamageType> DamageTypeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Barrel Attributes")
	USoundBase* HitSound;

private:
	
	bool HitScan(FVector ShotStart, FVector ShotDirection, FVector& ShotEnd, FHitResult ShotResult);

	UFUNCTION()
	void ProcessHit(const FHitResult& Hit, const FVector& Direction);
	
	APawn* GetOwningPawn() const;
	AController* GetController() const;
		
};
