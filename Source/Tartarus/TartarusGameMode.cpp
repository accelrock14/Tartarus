// Copyright Epic Games, Inc. All Rights Reserved.

#include "TartarusGameMode.h"
#include "TartarusCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATartarusGameMode::ATartarusGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
