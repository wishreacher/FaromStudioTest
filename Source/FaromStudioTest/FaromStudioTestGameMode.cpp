// Copyright Epic Games, Inc. All Rights Reserved.

#include "FaromStudioTestGameMode.h"
#include "FaromStudioTestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFaromStudioTestGameMode::AFaromStudioTestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
