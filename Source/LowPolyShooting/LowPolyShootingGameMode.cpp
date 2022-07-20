// Copyright Epic Games, Inc. All Rights Reserved.

#include "LowPolyShootingGameMode.h"
#include "LowPolyShootingCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALowPolyShootingGameMode::ALowPolyShootingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/Ybot/BP/BP_YBotCharacter"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
