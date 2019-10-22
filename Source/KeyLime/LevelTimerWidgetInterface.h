#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelTimerWidgetInterface.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddTimeDelegate, int, secondsAdded);

UCLASS(Blueprintable)
class KEYLIME_API ULevelTimerWidgetInterface : public UObject
{
	GENERATED_BODY()
public:
	ULevelTimerWidgetInterface() = default;
	void addTime(int secondsToAdd);

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FAddTimeDelegate onAddTimeDelegate;
};
