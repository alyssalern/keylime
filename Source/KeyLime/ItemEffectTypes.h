#pragma once
#include "Runtime/CoreUObject/Public/UObject/Class.h"

UENUM(BlueprintType)
enum ItemEffectType
{
	UNASSIGNED	UMETA(DisplayName="Unassigned"),
	SLOWDOWN	UMETA(DisplayName="Slowdown"),
	SPEEDUP		UMETA(DisplayName="Speedup"),
	GROW		UMETA(DisplayName="Grow"),
	SHRINK		UMETA(DisplayName="Shrink"),
	TELEPORT	UMETA(DisplayName="Teleport"),
	ADD_TIME	UMETA(DisplayName="Add Time")
};