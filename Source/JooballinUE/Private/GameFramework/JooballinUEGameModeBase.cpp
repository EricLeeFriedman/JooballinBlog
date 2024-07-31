// Copyright Epic Games, Inc. All Rights Reserved.


#include "JooballinUEGameModeBase.h"

#include "JooballinUEPlayerController.h"

AJooballinUEGameModeBase::AJooballinUEGameModeBase()
{
	PlayerControllerClass = AJooballinUEPlayerController::StaticClass();
}
