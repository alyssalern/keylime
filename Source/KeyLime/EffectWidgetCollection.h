#pragma once

class UCurrentEffectWidgetInterface;
class ULevelTimerWidgetInterface;

#include "EffectWidgetCollection.generated.h"

UINTERFACE()
class KEYLIME_API UEffectWidgetCollection : public UInterface
{
	GENERATED_BODY()
public:
	
};

class IEffectWidgetCollection
{
	GENERATED_BODY()
public:
	virtual UCurrentEffectWidgetInterface* getCurrentEffectWidgetInterface() const = 0;
	virtual ULevelTimerWidgetInterface* getLevelTimerWidgetInterface() const = 0;
};