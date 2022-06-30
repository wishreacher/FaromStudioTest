// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class AFaromStudioTestCharacter;
UCLASS()
class FAROMSTUDIOTEST_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	ABaseWeapon();
	
protected:
	virtual void BeginPlay() override;
	
	AFaromStudioTestCharacter* GetCharacterOwner() const;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;
private:
	AFaromStudioTestCharacter* CachedCharacterOwner;
};
