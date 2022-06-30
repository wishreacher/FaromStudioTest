// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FAROMSTUDIOTEST_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetPawn(APawn* InPawn) override;
	
protected:
	virtual void SetupInputComponent() override;

private:
	void StartFire();
	void StopFire();
	void Reload();
	
	TSoftObjectPtr<class AFaromStudioTestCharacter> CachedBaseCharacter;
};
