// License Copyright (c) 2025 Eric Friedman

#pragma once

/**
 * How to update the DOD actors.
 */
UENUM()
enum class EDODTickMode : uint8
{
	/** DOD actors update themselves. */
	Actor,

	/** DOD actors are updated by the DOD actor manager. */
	ActorByManager,

	/** The manager has the data and updates the data first, then updates the actors. */
	ManagerData,
};
