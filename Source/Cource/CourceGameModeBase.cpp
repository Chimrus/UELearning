// Copyright Epic Games, Inc. All Rights Reserved.


#include "CourceGameModeBase.h"

#include "Core/SandboxPawn.h"

ACourceGameModeBase::ACourceGameModeBase()
{
	DefaultPawnClass = ASandboxPawn::StaticClass();
}
