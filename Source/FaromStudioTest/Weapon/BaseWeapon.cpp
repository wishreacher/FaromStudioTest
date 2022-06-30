// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromStudioTest/Weapon/BaseWeapon.h"
#include "FaromStudioTest/FaromStudioTestCharacter.h"


ABaseWeapon::ABaseWeapon()
{
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

AFaromStudioTestCharacter* ABaseWeapon::GetCharacterOwner() const
{
	return IsValid(CachedCharacterOwner) ? CachedCharacterOwner : nullptr;
}
