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

AFaromStudioTestCharacter* ABaseWeapon::GetCharacterOwner()
{
	return IsValid(CachedCharacterOwner) ? CachedCharacterOwner : nullptr;
}

void ABaseWeapon::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	if(IsValid(NewOwner))
	{
		checkf(GetOwner()->IsA<AFaromStudioTestCharacter>(), TEXT("ABaseWeapon::SetOwner only AFaromStudioTestCharacter can own BaseWeapon"))
		CachedCharacterOwner = StaticCast<AFaromStudioTestCharacter*>(GetOwner());
	} else
	{
		CachedCharacterOwner = nullptr;
	}
}
