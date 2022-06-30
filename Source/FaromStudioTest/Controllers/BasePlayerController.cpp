// Fill out your copyright notice in the Description page of Project Settings.


#include "FaromStudioTest/Controllers/BasePlayerController.h"

#include "FaromStudioTest/FaromStudioTestCharacter.h"

void ABasePlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	CachedBaseCharacter = Cast<AFaromStudioTestCharacter>(InPawn);
}

void ABasePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ABasePlayerController::StartFire);
	InputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ABasePlayerController::StopFire);
	InputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ABasePlayerController::Reload);
}

void ABasePlayerController::StartFire()
{
	if(CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StartFire();
	}
}

void ABasePlayerController::StopFire()
{
	if(CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->StopFire();
	}
}

void ABasePlayerController::Reload()
{
	if(CachedBaseCharacter.IsValid())
	{
		CachedBaseCharacter->Reload();
	}
}
