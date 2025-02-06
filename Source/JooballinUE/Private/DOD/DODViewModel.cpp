// License Copyright (c) 2025 Eric Friedman

// Includes
// -------------------------------------
#include "DODViewModel.h"

// JooballinUE
#include "DODActorManager.h"

// Engine
#include "EngineUtils.h"

// SetDODTickMode
// -------------------------------------
void UDODViewModel::SetDODTickMode(const EDODTickMode InDODTickMode)
{
	for (TActorIterator<ADODActorManager> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		ActorItr->SetTickMode(InDODTickMode);
	}
}
