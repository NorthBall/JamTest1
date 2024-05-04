// Copyright Epic Games, Inc. All Rights Reserved.

#include "JamTest1GameMode.h"
#include "JamTest1Character.h"
#include "UObject/ConstructorHelpers.h"

AJamTest1GameMode::AJamTest1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
